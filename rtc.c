// we use 32 kHz oscillator builtin the AVR 128db28 as the source for RTC
// prescaler: div128

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "rtc.h"
#include "usart0.h"


void rtc_init() // max is ~65 seconds
{
 
    // enable overflow interrupt
    RTC.INTCTRL = RTC_OVF_bm;
    
    // use 32.768 kHz Internal Oscillator
    RTC.CLKSEL = RTC_CLKSEL_OSC32K_gc;
    
    // wait until RTC.PER is sync
    while (RTC.STATUS & RTC_PERBUSY_bm);
    //Set Period to 5s
    //0x0500 = 1280
    // 32.768 kHz div 128 = 256 ticks/s 
    
    RTC.PER = 0x0500; // 5s until sleep mode kicks in
    
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    RTC.CNT = 0x0000;
    
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    //Run the RTC in Standby, Prescaler is 128, Enable RTC
    RTC.CTRLA = RTC_PRESCALER_DIV128_gc | RTC_RTCEN_bm;
}
void rtc_stop_rtc()
{
  // reset all flag
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    RTC.CTRLA &= ~(RTC_RTCEN_bm);
}

void rtc_resume()
{
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    RTC.CTRLA |= (RTC_RTCEN_bm);
}

void rtc_restart()
{
    
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    
    //Turn off the RTC
    RTC.CTRLA &= ~(RTC_RTCEN_bm);
    
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    
    //Clear Counter
    RTC.CNT = 0x0000;
 
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    
    //Reset the RTC
    RTC.CTRLA |= RTC_RTCEN_bm;
}


