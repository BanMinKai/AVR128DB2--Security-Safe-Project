# AVR128DB2--Security-Safe-Project

This is the firmware for the project I did for ENEL300. This is my first ever firmware application, so there are still a lot of comments I leave behind as learning reference materials for myself later.
In this project of Security Safe, we use an AVR microcontroller 

    (1) to controll an electromagnet (12V ~50kg pullforce) using HIGH/LOW signal, and 
    (2) to read data from RFID module (RC522) using SPI, and
    (3) to read HIGH/LOW input from Motion Sensor module HC-SR501

The firmware design is to base on State Machine pattern. The main feature is to have 2 states: WAKE and SLEEP

    (1) when WAKE, the system checks data from RFID and motion sensor modules as in polling pattern.
    (2) when SLEEP, the system uses data from Motion Sensor as external interrupt source to wake the system up

