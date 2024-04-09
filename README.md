# AVR128DB2--Security-Safe-Project

Peripherals and Features used:

    - Real Time Counter (RTC)
    - SPI
    - USART
    - STANDBY SLEEP
    - Input/Sense Configuration (ISC, aka external interrupt)
    - State Machine Design Pattern
Tools used:

    - microcontroller (hardware): AVR128DB28
    - Debugger/Programmer (hardware): MPLAB Snap In-Circuti Debugger
    - IDE (software): MPLAB X IDE

Visualizations:

    - Sprint2 flowchart                      --> represents previous application structure,
                                                 which was not scalable as expected
    - Sprint3 State Machine state diagram    --> represents updated application structure, 
                                                 to incorporate sleep mode and external interrupt
    
![image](https://github.com/BanMinKai/AVR128DB2--Security-Safe-Project/assets/115819439/d927c3cb-0269-4323-a0b9-e54633951a12)

    

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

Hardware Layout and PCB schematics


    disclaimer: I was not the author of the PCB, I put it here for reference. 
    The PCB was skillfully desgined and completed by Graydon, a teammate in my ENEL300 group
I 
![image](https://github.com/BanMinKai/AVR128DB2--Security-Safe-Project/assets/115819439/b7ed3bd2-acee-4123-8f85-8df52c90407d)

![image](https://github.com/BanMinKai/AVR128DB2--Security-Safe-Project/assets/115819439/e692070c-5764-4bb3-803d-1bf9d3c201ce)

![image](https://github.com/BanMinKai/AVR128DB2--Security-Safe-Project/assets/115819439/f495bee4-a71c-4ae4-a4cf-fc330940a3c7)

3D Printed Housing

    disclaimer: the housing was designed and the final integration of circuitry 
    and 3D housing was completed by Temmulen, another teammate in my group
    
![image](https://github.com/BanMinKai/AVR128DB2--Security-Safe-Project/assets/115819439/84967fd8-1d60-4999-a6cb-e15d7966f0f9)


    

