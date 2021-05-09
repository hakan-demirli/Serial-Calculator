# Serial-Calculator

PIC18F4550 calculator with serial communication
![alt text](https://github.com/hakan-demirli/Serial-Calculator/blob/main/calculator.gif)

# Description
The main objective of this project is to familiarize myself with embedded processors and the datasheets.
PIC18F4550 processor reads the keypresses and forwards them to the serial port. QT serial port software receives those packets, calculates the answer, and sends it back to the PIC calculator. The whole operation is displayed on a 16x4 LCD screen.
Communication between the PIC that is emulated by Proteus8 and the QT software is achieved by [Virtual Serial Port Emulator](http://www.eterlogic.com/Products.VSPE.html).
Most of the options on the QT GUI are unimplemented. Also, serial calculator only works with the float options.
![alt text](https://github.com/hakan-demirli/Serial-Calculator/blob/main/QT_Terminal.png)

# This project is started on xx/01/2020 and hasn't been touched since then.  
