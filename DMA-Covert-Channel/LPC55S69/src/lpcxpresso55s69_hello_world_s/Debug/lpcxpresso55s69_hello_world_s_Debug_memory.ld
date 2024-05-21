/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2023
 * Generated linker script file for LPC55S69
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.7.1 [Build 9221] [2023-03-28] on Jun 27, 2023, 7:50:27 AM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 0xfe00 /* 65024 bytes (alias Flash) */  
  SG_veneer_table (rx) : ORIGIN = 0x1000fe00, LENGTH = 0x200 /* 512 bytes (alias Flash2) */  
  Ram0 (rwx) : ORIGIN = 0x30000000, LENGTH = 0x8000 /* 32K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x10000000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x10000000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x10000000 + 0xfe00 ; /* 65024 bytes */  
  __top_Flash = 0x10000000 + 0xfe00 ; /* 65024 bytes */  
  __base_SG_veneer_table = 0x1000fe00  ; /* SG_veneer_table */  
  __base_Flash2 = 0x1000fe00 ; /* Flash2 */  
  __top_SG_veneer_table = 0x1000fe00 + 0x200 ; /* 512 bytes */  
  __top_Flash2 = 0x1000fe00 + 0x200 ; /* 512 bytes */  
  __base_Ram0 = 0x30000000  ; /* Ram0 */  
  __base_RAM = 0x30000000 ; /* RAM */  
  __top_Ram0 = 0x30000000 + 0x8000 ; /* 32K bytes */  
  __top_RAM = 0x30000000 + 0x8000 ; /* 32K bytes */  
