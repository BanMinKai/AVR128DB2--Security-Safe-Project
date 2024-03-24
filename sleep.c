#include <avr/io.h>
#include <avr/sleep.h>

void activate_ISC() {
    PORTD.DIR &= ~PIN2_bm; // pinD2 as input 
    PORTD.PIN2CTRL |= PORT_ISC_RISING_gc; // interrupt sensing enabled
}

void deactivate_ISC() {
    PORTD.DIR &= ~PIN2_bm; // pin2 as input
    PORTD.PIN2CTRL = 0x00; // disable interrupt sensing
    // 0x00 means pin still serving as a place for input but
    // it does not sense rising, falling edge... 
}

void sleep_init() {
    set_sleep_mode(SLEEP_MODE_STANDBY);
    //set_sleep_mode(SLEEP_MODE_PWDOWN);

}

void sleep_start() {
    activate_ISC();
    sleep_mode();
}

