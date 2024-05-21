Introduction
============

This example demonstrates the use of TrustZone for Cortex-M device by isolating
temperature sensor driver source code from non-secure world.

The non-secure application will request to read temperature from secure world
via secure gateway, and then print result in EDBG Virtual COM Port per second.
The non-secure application will also toggle a LED per second.

There are two combined projects for the example:

* TZ-SecureDriver-S Example for Secure Project
* TZ-SecureDriver-NS Example for non-secure Project


Supported evaluation kit
------------------------
 - ATSAML11-XPRO


Drivers & Middleware in Secure Project
--------------------------------------
* TrustZone middleware

  * Configure memory and peripherals secure attribution
  * Configure Port Security Attribution of I/O Pins
  * Configure NVIC Interrupt Target Non-Secure state
  * Enable related secure gateway veneer code

* Synchronous I2C Master

  * Secure peripheral, used to access temperature sensor

* AT30TSE75X middleware


Drivers & Middleware in Non-Secure Project
------------------------------------------
* STDIO Redirect middleware
* Synchronous USART (EDBG Virtual COM Port)
* GPIO (non-secure LED I/O pin)


Debugging the example with Atmel Studio
---------------------------------------

#. Download the TZ-SecureDriver secure project and non-secure project from START
#. Import the secure project into Atmel Studio and compile it
#. In secure project solution, import the non-secure project with "Add To Solution" option, and then compile non-secure project
#. Open properties dialog of secure project, add elf file of non-secure project into "Advanced->Additional module"
#. Open properties dialog of non-secure project, add elf file of secure project into "Advanced->Additional module"
#. Start debugging
