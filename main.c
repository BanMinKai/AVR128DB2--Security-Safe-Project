#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdio.h>
#include "mfrc522.h"
#include "usart0.h"
#include "spi0.h"
#include <avr/interrupt.h>
#include "mfrc522_api.h"
#include "sleep.h"

//------------------------------------------------------------------------------

// I try to use State Machine Design Pattern
// states are defined using enum and typedef
// basically enum is used to word-dress meaningless numbers like 0,1,2,3...
enum states {
    STATE_SLEEP = 0,
    STATE_WAKE,
};
typedef enum states state_t;
state_t current_state;


// convenient functions, basically name-dress all the register assignment
// 2 styles either use actual functions or #define functions
void unlock() {
    PORTD.OUT &= ~(1 << PIN7);
}

void lock() {
    PORTD.OUT |= (1 << PIN7);
}
#define read(PORT,PIN) ((PORT.IN & (1 << PIN)) >> PIN)
#define sensor_is_high (read(PORTD,PIN2) == 1)
#define sensor_is_low  (read(PORTD,PIN2) == 0)

// variables needed for applications
uint8_t SelfTestBuffer[64];
//uint8_t tag_id[8] = {0x14,0x63,0x97,0x6A,0x8A,0x80,0x80,0x80};
// somehow the tag has 5 bytes in the uid :>
#define sensor_is_whatever 0
#define KEY_FOUND 1

//MAIN--------------------------------------------------------------------------
int main()
{
    // GPIO init
    // OUTPUT: 
    //       A0 for Tx, A4 for MOSI, A6 for SCK, A7 for not_SS
    //       D7 for electromagnet
    // INPUT:
    //       D2 for sensor, as input (default) and as interrupt source (ISC written)
    //       to enable D2 as external interrupt source
    //       write to PORTD.PIN2CTRL 
    PORTA.DIR = PIN0_bm | PIN4_bm | PIN6_bm | PIN7_bm; 
    PORTA.OUT = 0x80;
    PORTD.DIR = 0x80; // Pin D7 output for LED & Pin D2 as input for SENSOR
    PORTD.OUT &= ~(1 << PIN7); // turn electromagnet off
 
    // init of other peripherals used
    usart_init();
    spi_init();
    mfrc522_init();
    rtc_init();
    rtc_stop_rtc();
    sleep_init();
    sei(); // my style is always put sei() where i can see easily
    
    // what the application does when just powered on
    // check version of the reader of the RFID module
    // if  no reader found, likely broken, you need to replace your RFID module
	uint8_t byte;
	uint8_t str[MAX_LEN] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	usart_printf("RFID Reader\r\n");
    
	//check version of the reader
	byte = mfrc522_read(VersionReg);
	if(byte == 0x92)
	{
		usart_printf("MIFARE RC522v2\r\n");
		
	}
    else if(byte == 0x91 || byte==0x90)
	{
		usart_printf("MIFARE RC522v1\r\n");
	}
    else
	{
		usart_printf("No reader found\r\n");
	}
	
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	_delay_ms(500);  // somehow, i dont know why it does no count properly
    // like _delay_ms(1000) delays way shorter than 1000s
    
    
    // initial state is sleep
    // NOTE: SO 
    current_state = STATE_WAKE;
    rtc_restart();
    lock();
    
    while(1){
        // as my first time implementing
        // I got a lot of problems with array of state_functions 
        // so I stick with simpler implementation, using switch case
        // still I used enum and typedef :> make the code feel like
        // half-ok state machine
        switch (current_state) {
            case STATE_SLEEP:
                // turn off 
                PORTD.OUT &= ~(PIN7_bm);
                usart_printf("enter sleep mode\r\n");
                
                // wrap the function sleep_start() with 2 delays to give it sometime to 
                // stabilize before sleep and after sleep
                _delay_ms(50);
                sleep_start();
                _delay_ms(50);
                usart_printf("just woke up\r\n");
                rtc_restart();  //this may fix the too-short interrupt flaw 
                break;
            case STATE_WAKE:
                //lock();
                usart_printf("wake\r\n"); // keep ouputting "Wake" in Data Visualizer MPLAP
                byte = mfrc522_api_scan_for_key(str);
                
                if (sensor_is_high) {
                    lock();
                    rtc_restart();
                    _delay_ms(250);
                }
                
                if (byte == KEY_FOUND) {
                    unlock();
                    usart_printf("KEY FOUND, UNLOCK & WAIT\r\n");
                    rtc_stop_rtc();
                    _delay_ms(4*3000);
                    rtc_restart();
                    lock();
                    
                } 
                
                _delay_ms(250);
                break;
            default: 
                current_state = STATE_SLEEP;
                break;
        }
    }
}
                
// also, I prefer to put ISR in main.c because
// ISR usually have to include functions from application layer
// we can go with "callback" and keep ISR in its own peripheral library
// I am still learning and placing ISR in main is the best way I could do right now
ISR(PORTD_PORT_vect) {
    current_state = STATE_WAKE;
    PORTD.INTFLAGS |= PIN2_bm; // clear interrupt flag
}

//// THERE IS A FLAW HERE, IF THE INTERRUPT IS NOT HELD LONG ENOUGH
/// THEN THE SYSTEM IS WAKEN UP BUT NOT FALL INTO "sensor is high"
/// THEN NO RTC IS RESTARTED
/// ONE METHOD TO FIX IS TO RESTART RTC WHEN JUST WAKING UP

ISR(RTC_CNT_vect)
{
    rtc_stop_rtc();
    usart_printf("rtc stops\r\n");
    current_state = STATE_SLEEP;
    RTC.INTFLAGS |= RTC_OVF_bm;
}
