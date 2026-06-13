#ifndef __BUS_SIDE_CHANNEL_H
#define __BUS_SIDE_CHANNEL_H

#include "main.h"

#define OFFSET 18 // clock offset where we want the collosion to happen
#define ICACHE_EN   1
#define ICACHE_DIS  0


void get_trace(void (*victim)(),  int ICache_EN);
void get_trace_find_clocks(void (*victim)(), int ICache_EN);
void autonomous_single_trace(int first_clock,
                            int next_iteration_time,
                            int next_loop_time,
                            void (*victim)());

#endif //__BUS_SIDE_CHANNEL_H