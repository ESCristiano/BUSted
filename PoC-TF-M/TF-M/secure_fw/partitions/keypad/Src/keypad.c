#include "keypad.h"

char pin[PIN_LEN];

int init = 0;
int key_state = 0;
int current_key_state = 0;
int pin_idx = 0;
int dummy_pin_idx = 0;
char dummy_pin[PIN_LEN];

// "nop" instruction cannot be used, because it is not reliable! Sometimes it
// last 1 clock other times 0 clocks. Even with -o0 and the actual nop being
// present in the asm code. The processor sometimes does not execute the
// nop instructions
#define NOP()  __asm volatile("mov r8,r8")

//GPIO port input data register 
#define IDR_REG  0x10

// // C1 Port and PINS
// #define GPIOB_BASE 0x52020400

// // C2/3/4 Port and PINS
// #define GPIOA_BASE 0x52020000


// This function is a replica of HAL_GPIO_WritePin. For some reason it was giving
// a hardfaults using the HAL_GPIO_WritePin, in get_keypad_state but not in 
// MX_GPIO_Init. Strange! 
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if(PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
  }
}

#define READ_R1() !(!(*R1 & R1_Pin))
#define READ_R2() !(!(*R2 & R2_Pin))
#define READ_R3() !(!(*R3 & R3_Pin))
#define READ_R4() !(!(*R4 & R4_Pin))

#define WRITE_C1(PIN_STATE) GPIO_WritePin(C1_GPIO_Port, C1_Pin, PIN_STATE)
#define WRITE_C2(PIN_STATE) GPIO_WritePin(C2_GPIO_Port, C2_Pin, PIN_STATE)
#define WRITE_C3(PIN_STATE) GPIO_WritePin(C3_GPIO_Port, C3_Pin, PIN_STATE)
#define WRITE_C4(PIN_STATE) GPIO_WritePin(C4_GPIO_Port, C4_Pin, PIN_STATE)

__attribute__((optimize(0))) int get_keypad_state(){
  int key = 0, reset = 0;
  int *R1=(int *)(GPIOA_BASE_S+IDR_REG),
      *R2=(int *)(GPIOA_BASE_S+IDR_REG),
      *R3=(int *)(GPIOA_BASE_S+IDR_REG),
      *R4=(int *)(GPIOB_BASE_S+IDR_REG);
  for(int i = 0; i < 4; i++){
    reset = 1 << i;
    WRITE_C1(!(0x1 & reset));
    WRITE_C2(!(0x2 & reset));
    WRITE_C3(!(0x4 & reset));
    WRITE_C4(!(0x8 & reset));
    key |= (READ_R1()) << (0+4*i);
    key |= (READ_R2()) << (1+4*i);
    key |= (READ_R3()) << (2+4*i);
    key |= (READ_R4()) << (3+4*i);
    //We need to wait some cycles, otherwise we will sometimes read wrong values
    NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
    NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
    NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
  }
  return (~key)&0x0000ffff;
}
/* 
 * Fetch and process key state from keypad driver SM.
 * NOTE: we do _not_ early out the for loop below upon detecting a key access
 * to prevent side-channel leakage of key presses via execution time.
 * 
 * TODO: C Balanced code -> const time & (cache-line aligned) 
 * 
 * This code is based in Nemesis and Sancus poll_keypad code
 */
__attribute__((optimize(0))) int read_keypad(void)
{
    int is_pressed, mask = 0x1;
    // int new_key_state = (1<<2); 
    int new_key_state = get_keypad_state();
    
    for (int key = 0; key < KYPD_NB_KEYS; key++)
    { 
        // detect rising edge
        is_pressed = (new_key_state & mask) & ~(key_state & mask);
        if (is_pressed)
          pin[pin_idx++] = key;
        else
          dummy_pin[dummy_pin_idx++] = key;
        dummy_pin_idx = 0; //avoid buffer overflow
        mask <<= 1;
    }
    key_state = new_key_state;
    return (PIN_LEN - pin_idx);
}

__attribute__((optimize(0)))  void read_pin(){
  int pin_len = 1;
  while(pin_len){
    pin_len = read_keypad();
  }
  pin_idx = 0;
}

// Just for test porpuses
__attribute__((optimize(0))) int read_keypad_get_trace(void)
{
    int is_pressed, mask = 0x1;
    int new_key_state = get_keypad_state();

    for (int key = 0; key < 16; key++)
    // for (int key = 0; key < KYPD_NB_KEYS; key++)
    { 
        // detect rising edge
        is_pressed = (new_key_state & mask) & ~(key_state & mask);
        if (is_pressed)
          pin[pin_idx++] = key;
        else
          dummy_pin[dummy_pin_idx++] = key;
        pin_idx = 0; 
        // dummy_pin_idx = 0; //avoid buffer overflow
        mask <<= 1;
    }
    key_state = new_key_state;
    return (PIN_LEN*16 - dummy_pin_idx);
    // return (PIN_LEN - pin_idx);
}

__attribute__((optimize(0))) void read_pin_get_trace(){
  int pin_len = 1;
  while(pin_len){
    pin_len = read_keypad_get_trace();
  }
  dummy_pin_idx = 0;
  // pin_idx = 0;
}