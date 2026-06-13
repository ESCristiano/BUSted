#ifndef COVERT_H
#define COVERT_H
  
#include "board.h"
//#include "test_configs.h"
  //--------- MACROS for NS world Configs -----------------------
    // Macro REVERSE_ENG_CACHE is used to activate the test
    // to determine the cache configuration. Use the flag 
    // REVERSE_ENG_CACHE with  TEST_DIRECT_MAPPED or TEST_2_WAYS 
     
      //#define REVERSE_ENG_CACHE
      //  // #define TEST_DIRECT_MAPPED
      //  #define TEST_2_WAYS
    //------------------------------------------------------
    // Macro TROJAN_S used to activate the meausre of the 
    // covert-channel between S and NS world. If commented
    // it will measure the natice channel of the board without
    // the S world interference 
      // #define TROJAN_S 
    //--------------------------------------------------------
    // Macro NS_NON_CACHEABLE put all the NS code non-cacheanle
    // and Macro ONLY_PRIME_CACHEABLE put only code that will 
    // be mapped to cache as cacheable. The rest of the NS code
    // is setted as non-cacheable to reduce noise
      //#define NS_NON_CACHEABLE
      // #define ONLY_PRIME_CACHEABLE 
  //-------------------------------------------------------------- 

  //-----------------TEST CONFIGS TEST 1 --------------------------------
  //-------- Uncomment this to measure the Native Channel
    //#define ONLY_PRIME_CACHEABLE 
  
  //-------- Uncomment this to measure the covert channel with tfm
    #define TROJAN_S 
    #define ONLY_PRIME_CACHEABLE 
 
  //-------- Uncomment this to measure the covert channel with cache invalidation
  //...... Not appliable to Nuvuton m2351
  //...... Nordic -> Only appliable if tfm level 1
    // #define TROJAN_S 
    // #define ONLY_PRIME_CACHEABLE 
    // #ifdef NORDIC_NRF9160
    //     # define NORDIC_NRF9160_CACHE_INVALIDATION
    // #endif
    // #ifdef STM32L552
    //     #define STM32L552_CACHE_INVALIDATION
    // #endif
    // #ifdef MUSCA_B1
    //     #define MUSCA_B1_CACHE_INVALIDATION
    // #endif
    
  //-------- Uncomment this to measure the covert channel with NS non cacheable
  //...... Not appliable to Nuvuton m2351
    // #define TROJAN_S 
    // #define NS_NON_CACHEABLE
  
  //-------- Uncomment this to measure the covert channel with cache disable
  //...... Not appliable to Nuvuton m2351
  //...... Nordic -> Only appliable if tfm level 1
    //#define TROJAN_S 
    //#ifdef NORDIC_NRF9160
        //# define NORDIC_NRF9160_CACHE_DISABLE 
    //#endif

  //-----------------TEST CONFIGS TEST 2 --------------------------------
    //#define TEST_2_SEC_1
  //-------- Uncomment this to measure the impact to do or not a printf 
  //--------in terms of cache pattern (cache usage)
    // #define ONLY_PRIME_CACHEABLE 
    //#define PRINTF_CACHE_PATTERN
  //-------- Uncomment this to get the pattern to execute two hash operations 
  //--------with different messages and results, one valid other not
     #define HASH_CACHE_PATTERN
     // #define ONLY_PRIME_CACHEABLE 
  //-------- Uncomment this to get the pattern to execute two hash operations 
  //--------with different messages 
    // #define ONLY_PRIME_CACHEABLE 
    //#define AES_CACHE_PATTERN
  
  //-----------TEST 3
  #define TEST_3_SEC_1

  // #ifndef REVERSE_ENG_CACHE
  //   #define I_N_CACHE_SETS    I_CACHE_SIZE/(I_CACHE_LINE_SIZE*I_N_WAYS)
  // #else
  //   #define I_N_CACHE_SETS    I_CACHE_SIZE/(I_CACHE_LINE_SIZE*(I_N_WAYS/I_N_WAYS)) // assume that the cahce is direct-mapped for test porpuses 
  // #endif

  //extern void block_jumps_0_0();
  extern void prime_set_0_way_0();
  extern void probe_set_0_0();
  
  extern void second_prime_set_0_way_0();

  //extern void block_bx_lr_way_0();
  //extern void block_bx_lr_last_way();
  extern void probe_set_0_way_0();
  extern void probe_set_0_way_1();
  extern void probe_set_0_way_2();
  extern void probe_set_0_way_3();
  
  // touch_s uses the same block of jumps of the prime 1 
  __attribute__ ((noinline)) void touch_s(int secret){
    void (*func_ptr)(void)=(&prime_set_0_way_0+1+((I_N_CACHE_SETS-secret-1)*I_CACHE_LINE_SIZE));
    func_ptr();
  }

  // touch_ns uses the same block of jumps of the prime 2
  __attribute__ ((noinline)) void touch_ns(int secret){
    void (*func_ptr)(void)=(&second_prime_set_0_way_0+1+((I_N_CACHE_SETS-secret-1)*I_CACHE_LINE_SIZE));
    func_ptr();
  }


  // ensure that the code is compiled withou otimizations otherwise we can have false results
  // Non Secure (or S tf-m level 1) is doing the prime and probe
  __attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_all(){
    volatile int time1, time2, result;
    SysTick->CTRL = 0x0;
    SysTick->LOAD  = (uint32_t)(0xFFFFFF - 1); //mac counter value
    SysTick->VAL = 0; // reset the val  counter
    SysTick->CTRL = 0x05; // starts the systick
    time1 = SysTick->VAL;
    #ifndef REVERSE_ENG_CACHE
      prime_set_0_way_0();
    #else
      touch_s(I_N_CACHE_SETS/2);
    #endif
    time2 = SysTick->VAL;
    result = time1 - time2; // inverted subtraction because it is a down counter
    SysTick->CTRL = 0x0; // stops the systick
    SysTick->VAL = 0; // reset the val  counter
    return result;
  }

//----------------------------------------------------------------------------------
// Wall-clocks definitions (Board Peripheral Timers)
//----------------------------------------------------------------------------------
#ifdef STM32L552
  #define UP_COUNTER
  int *ptr_ctr = 0x50001000, *ptr_cnt = 0x50001000+0x24, *rcc_ctrl = 0x50021000+0x058;
  
  // use these "functions" as a MACRO to reduce cache polution. These functions will be called
  // in a __attribute__((optimize(0))) function, so inline functions are not allowed
  #define config_timer()(*rcc_ctrl = *rcc_ctrl | (1<<4))
  #define enable_timer()(*ptr_ctr = (*ptr_ctr)|1<<0)
  #define disable_timer()(*ptr_ctr = (*ptr_ctr)&~(1<<0))

#endif 

#ifdef PSoC64
  // NOTE: Timer0 of TCPWM0 is only for S world. If it is needed a counter in NS, 
  // timer1 of TCPWM0
  #include "cy_tcpwm_counter.h"
  #define UP_COUNTER
  #define COUNTER_NUMBER 0
  cy_stc_tcpwm_counter_config_t tcpwm_counter_config =
  {
    /* .period            = */ 65000UL, /* Period of 100 (0-99). Terminal count event when rolls over back to 0. */
    /* .clockPrescaler    = */ CY_TCPWM_COUNTER_PRESCALER_DIVBY_1, /* Clk_counter = Clk_input / 4 */
    /* .runMode           = */ CY_TCPWM_COUNTER_CONTINUOUS, /* Wrap around at terminal count. */
    /* .countDirection    = */ CY_TCPWM_COUNTER_COUNT_UP, /* Up counter, counting from 0 to period value. */
    /* .compareOrCapture  = */ CY_TCPWM_COUNTER_MODE_COMPARE, /* Trigger interrupt/event signal when Counter value is equal to Compare0 */
    /* .compare0          = */ 65000UL,
    /* .compare1          = */ 0UL,
    /* .enableCompareSwap = */ false, /* Upon a compare event, swap the Compare0 and Compare1 values. */
    /* .interruptSources  = */ CY_TCPWM_INT_NONE,
    /* .captureInputMode  = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
    /* .captureInput      = */ CY_TCPWM_INPUT_0,
    /* .reloadInputMode   = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
    /* .reloadInput       = */ CY_TCPWM_INPUT_0,
    /* .startInputMode    = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
    /* .startInput        = */ CY_TCPWM_INPUT_0,
    /* .stopInputMode     = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
    /* .stopInput         = */ CY_TCPWM_INPUT_0,
    /* .countInputMode    = */ CY_TCPWM_INPUT_LEVEL, /* Set this input to LEVEL and 1 (high logic level) */
    /* .countInput        = */ CY_TCPWM_INPUT_1 /* So the counter will count input clock periods (Clk_counter, taking into account the clock prescaler) */
  };

  int *ptr_ctr_set = &TCPWM0->CTRL_SET, *ptr_ctr_clr = &TCPWM0->CTRL_CLR, 
        *ptr_start = &TCPWM0->CMD_START, *ptr_stop = &TCPWM0->CMD_STOP,
        *ptr_cnt = &TCPWM0_CNT0->COUNTER;

  // use these "functions" as a MACRO to reduce cache polution. These functions will be called
  // in a __attribute__((optimize(0))) function, so inline functions are not allowed

  #define config_timer() Cy_TCPWM_Counter_Init(TCPWM0, COUNTER_NUMBER, &tcpwm_counter_config)

  #define enable_timer() do {\
      *ptr_ctr_set = *ptr_ctr_set|1<<COUNTER_NUMBER; \
      *ptr_start = (*ptr_start)|1<<COUNTER_NUMBER;\
      } while(0)

  #define disable_timer() do {\
      *ptr_stop = (*ptr_stop)|1<<COUNTER_NUMBER;\
      *ptr_ctr_clr = *ptr_ctr_clr|1<<COUNTER_NUMBER; \
      } while(0)

#endif 

#ifdef MUSCA_B1
  #define DOWN_COUNTER

  int *ptr_ctr = 0x50000000, *ptr_cnt = 0x50000000+0x04, *ptr_reload = 0x50000000+0x08;
  
  // use these "functions" as a MACRO, to reduce cache polution and because they will be called
  // in a __attribute__((optimize(0))) function, so inline functions are not allowed
  #define config_timer()(*ptr_reload = 0x0FFFFFFF)
  #define enable_timer()(*ptr_ctr = (*ptr_ctr)|1<<0)
  #define disable_timer()(*ptr_ctr = (*ptr_ctr)&~(1<<0))

#endif 
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
__attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_all_s(){
  volatile int time1, time2;
  config_timer();
  enable_timer();
  time1 = *ptr_cnt;
  #ifndef REVERSE_ENG_CACHE
    prime_set_0_way_0();
  #else
    touch_s(I_N_CACHE_SETS/2);
  #endif
  time2 = *ptr_cnt;
  disable_timer();
   #ifdef UP_COUNTER
    return (time2 - time1);
  #endif
  #ifdef DOWN_COUNTER
    return (time1 - time2);
  #endif
}

// ensure that the code is compiled without otimizations otherwise we can have false results
  // Non Secure (or S tf-m level 1) is doing the prime and probe
__attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_line(int line, int way){
  volatile int time1, time2, result;
  void (*func_ptr)(void);
  SysTick->CTRL = 0x0;
  SysTick->LOAD  = (uint32_t)(0xFFFFFF - 1); //max counter value
  SysTick->VAL = 0; // reset the val  counter
  #if I_N_WAYS > 1
  if(!way)
  #endif
    func_ptr = (&probe_set_0_way_0+1+((line)*I_CACHE_LINE_SIZE));
  #if I_N_WAYS > 1
  else
    func_ptr = (&probe_set_0_way_1+1+((line)*I_CACHE_LINE_SIZE));
  #endif
  SysTick->CTRL = 0x05; // starts the systick
  time1 = SysTick->VAL;
  func_ptr();
  time2 = SysTick->VAL;
  result = time1 - time2; // inverted subtraction because it is a down counter
  SysTick->CTRL = 0x0; // stops the systick
  SysTick->VAL = 0; // reset the val  counter
  return result;
}

// ensure that the code is compiled withou otimizations otherwise we can have false results
__attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_line_s(int line, int way){
  volatile int time1, time2;
  void (*func_ptr)(void);
  config_timer();
  #if I_N_WAYS > 1
  if(!way)
  #endif
    func_ptr = (&probe_set_0_way_0+1+((line)*I_CACHE_LINE_SIZE));
  #if I_N_WAYS > 1
  else
    func_ptr = (&probe_set_0_way_1+1+((line)*I_CACHE_LINE_SIZE));
  #endif
  enable_timer();
  time1 = *ptr_cnt;
  func_ptr();
  time2 = *ptr_cnt;
  disable_timer();
  #ifdef UP_COUNTER
    return (time2 - time1);
  #endif
  #ifdef DOWN_COUNTER
    return (time1 - time2);
  #endif
}

void prime(){
  prime_set_0_way_0();
}

void prime_2(){
  second_prime_set_0_way_0();
}

  //   volatile int time1, time2, result;
  // __attribute__((optimize(0))) __attribute__ ((noinline)) volatile int fetch_1_way(){
  //   __asm("push {lr}");
  //   // second push from memory 
  //  //SysTick->CTRL = 0x05; // starts the systick
  //   __asm("ldr r0, =0xE000E010"); 
  //   __asm("mov r1, #5"); 
  //   __asm("str r1, [r0]");
    
  //   __asm("ldr r0, =0xE000E018"); 
  //   //read systick
  //   __asm("ldr r1, [r0]"); 
  //     //jump
  //     __asm("bl touch_2_ways"); // last instruction "Page 1" (bx)
  //   //read systick
  //   __asm("ldr r2, [r0]"); 
  //   //time1 = SysTick->VAL
  //   __asm("ldr r3, =time1");
  //   __asm("str r1, [r3]"); 
  //   //time2 = SysTick->VAL;
  //   __asm("ldr r3, =time2");
  //   __asm("str r2, [r3]"); 
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   result = (time1 - time2); // inverted subtraction because it is a down counter
  //   __asm("pop {lr}"); // This instruction in m23 gives a compiler error
  //   return result;
  // }


  // __attribute__((optimize(0))) __attribute__ ((noinline)) volatile int fetch_2_ways(){
  //   volatile int time1, time2, result;
  //   __asm("push {lr}");
  //   // second push from memory 
  //   SysTick->CTRL = 0x05; // starts the systick
  //   time1 = SysTick->VAL;
  //   __asm("bl touch_2_ways"); // last instruction "Page 1" (bx)
  //   time2 = SysTick->VAL;
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   result = (time1 - time2); // inverted subtraction because it is a down counter
  //   __asm("pop {lr}"); // This instruction in m23 gives a compiler error
  //   return result;
  // }

  // __attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_2_without_delay(){
  //   volatile int time1, time2, time3, time4, result;
  //   __asm("push {lr}");
  //   // second push from memory 
  //   SysTick->CTRL = 0x05; // starts the systick
  //   time1 = SysTick->VAL;
  //   __asm("bl ret_way_1"); // last instruction "Page 1" (bx)
  //   time2 = SysTick->VAL;
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   // necessário ter este time3, para o tempo ficar o mesmo da  probe_2_with_delay
  //   //porque tenho de ter um delay nessa 
  //   SysTick->CTRL = 0x05; // starts the systick
  //   time3 = SysTick->VAL;
  //   __asm("bl ret_way_2"); // last instruction "Page 2" (bx)
  //   time4 = SysTick->VAL;
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   result = (time1 - time2) + (time3 - time4); // inverted subtraction because it is a down counter
  //   __asm("pop {lr}"); // This instruction in m23 gives a compiler error
  //   return result;
  // }

  // __attribute__((optimize(0))) __attribute__ ((noinline)) volatile int probe_2_with_delay(){
  //   volatile int time1, time2, time3, time4, result;
  //   __asm("push {lr}");
  //   // second push from memory 
  //   SysTick->CTRL = 0x05; // starts the systick
  //   time1 = SysTick->VAL;
  //   __asm("bl ret_way_1"); // last instruction "Page 1" (bx)
  //   time2 = SysTick->VAL;
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   // second push from memory after delay
  //   //for (int i = 0; i < 24; ++i);
  //   /*__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
  //   __asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
  //   __asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");*/
  //   SysTick->CTRL = 0x05; // starts the systick
  //   time3 = SysTick->VAL;
  //   __asm("bl ret_way_2"); // last instruction "Page 2" (bx)
  //   time4 = SysTick->VAL;
  //   SysTick->CTRL = 0x0; // stops the systick
  //   SysTick->VAL = 0; // reset the val  counter
  //   result = (time1 - time2) + (time3 - time4); // inverted subtraction because it is a down counter
  //   __asm("pop {lr}"); // This instruction in m23 gives a compiler error
  //   return result;
  // }


#endif