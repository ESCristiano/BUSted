#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "main.h"

#define KYPD_NB_KEYS 16
#define PIN_LEN 4
extern char pin[PIN_LEN];

void read_pin();

#endif /* __KEYPAD_H */
