# AVR128DB2--Security-Safe-Project

Peripherals and Features:
    - Real Time Counter (RTC)
    - SPI
    - USART
    - STANDBY SLEEP
    - Input/Sense Configuration (ISC, aka external interrupt)
    - State Machine Design Pattern
Tools:
    - microcontroller (hardware): AVR128DB28
    - Debugger/Programmer (hardware): MPLAB Snap In-Circuti Debugger
    - IDE (software): MPLAB X IDE
    

This is the firmware for the project I did for ENEL300. This is my first ever firmware application, so there are still a lot of comments I leave behind as learning reference materials for myself later.
In this project of Security Safe, we use an AVR microcontroller 

    (1) to controll an electromagnet (12V ~50kg pullforce) using HIGH/LOW signal
    (2) to read data from RFID module (RC522) using SPI
    (3) to read HIGH/LOW input from Motion Sensor module HC-SR501

The firmware design is to base on State Machine pattern. The main feature is to have 2 states: WAKE and SLEEP

    (1) when WAKE, the system checks data from RFID and motion sensor modules as in polling pattern.
    (2) when SLEEP, the system uses data from Motion Sensor as external interrupt source to wake the system up
    (3) when input from Motion Sensor is LOW continously for 5 seconds, the system enters sleep mode (STANDBY)
    (3) Real Time Counter (RTC) are used to time this 5 seconds
    

