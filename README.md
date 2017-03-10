Embedded Lua
============

Demonstration of Lua running in interactive mode in the like-posix shell.

  - runs the like-posix shell on an stm32 serial port (115200baud)
  - exposes lua as a shell command. 

boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P
 - Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.


test
----

 - run a serial-terminal program, hit enter a few times then enter "lua".
