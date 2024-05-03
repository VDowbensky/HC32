================================================================================
                                Sample instructions
================================================================================
Version history 
date      version principal         IAR     MDK   description
2018-05-04  0.1     CJ             7.70    5.16  first version
================================================================================
Functional description
================================================================================
This example mainly involves the serial host data transmission function.

Description：
Configure PA02 and PA03 as UART transceiver ports.
Configure the baud rate to 9600bps
Enable UART transceiver function
================================================================================
test environment
================================================================================
Test board:
HC32L136_STK
---------------------
(required)

Auxiliary tools:
---------------------
DuPont line

Auxiliary software:
---------------------

================================================================================
Steps for usage
1. Connect the RX and TX of the board 1 to the TX and RX of the board 2 respectively with the DuPont line.
2, separately burn the master and slave code
3. The simulation enters the slave board and sets the breakpoint at the end of the code.
4. Reset the host board to resend the data.
5. Simulate whether the slave receives data normally 0xaa, 0x55
6. Simulate whether the host receives data normally 0xaa, 0x55

================================================================================

================================================================================
note:
================================================================================
no
================================================================================
