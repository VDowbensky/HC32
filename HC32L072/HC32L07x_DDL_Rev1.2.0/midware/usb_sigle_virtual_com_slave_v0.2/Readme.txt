================================================================================
                                Sample usage instructions
================================================================================
Version History
Date          Version     Owner         IAR      MDK  Description
2019-06-24       0.1      lsq           8.30    5.26  first version
================================================================================
Functional Description
================================================================================
Description:
This example demonstrates the USB emulation serial communication function. The 
host computer sets the serial communication parameters (port, baud rate, data 
bits, parity, and stop bits). After connecting, the host computer uses the Serial
 Debug Assistant to send data to the MCU. When the last data received is 0x0d, 
 the MCU sends a string back to the host computer.
================================================================================
Test environment
================================================================================
Test board:
---------------------
HC32LF07X-EVB-V11

Assistive tools:
---------------------

Assistive software:
---------------------

================================================================================
How to use
================================================================================
1) Open the project and recompile;
2) Enable the IDE's download and debugging functions;
3) Run the program;
4) Send data from the host computer to the MCU, ending with 0x0d. When the MCU 
receives the data, it will send the following string:
    "this is a sample about usb cdc"

================================================================================
Notice
================================================================================
 

================================================================================
