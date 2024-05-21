/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2023
 * Generated linker script file for LPC55S69
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.7.1 [Build 9221] [2023-03-28] on Jun 27, 2023, 7:50:30 AM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x10000, LENGTH = 0x72000 /* 456K bytes (alias Flash) */  
  Ram0 (rwx) : ORIGIN = 0x20008000, LENGTH = 0x2b000 /* 172K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x10000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x10000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x10000 + 0x72000 ; /* 456K bytes */  
  __top_Flash = 0x10000 + 0x72000 ; /* 456K bytes */  
  __base_Ram0 = 0x20008000  ; /* Ram0 */  
  __base_RAM = 0x20008000 ; /* RAM */  
  __top_Ram0 = 0x20008000 + 0x2b000 ; /* 172K bytes */  
  __top_RAM = 0x20008000 + 0x2b000 ; /* 172K bytes */  
