file-io-demo
===========

Demonstrates posix like devive IO.

the demo:

  - installs the console USART as a readonly device in /dev/ttyS0
  - attaches a logger to to STDOUT (which happens to be the console USART tx device)
 
then loops:
 
 - reads from that device
 - if there is data
	 - stores it to a file "datafile.txt"
	 - then back to the top
 - if not
	 - logs the size of the file to STDOUT
	 - waits a second
	 - then back to the top

boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P
 - Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.


test
----

 - run a serial-terminal program to monitor the board console output.

 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```
