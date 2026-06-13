/*
 * 
 * FILE created by cris, this is not part of this tf-n version. This file
 * Only existes in some boards like mps2/an521
 * 
 */

#include "cmsis.h"
#include "spm_ipc.h"
#include "tfm_hal_interrupt.h"
#include "tfm_peripherals_def.h"
#include "load/interrupt_defs.h"

/* struct irq_t {
    void                   *p_pt;
    struct irq_load_info_t *p_ildi;
}; */

static struct irq_t save_tfm_timer_irq_info = {0};

// This name is board specific. It's dependent of the timer used to generate the interrupt
void TIM7_IRQHandler(void)
{
    //Integrating the Interrupt Handling Function
    spm_handle_interrupt(save_tfm_timer_irq_info.p_pt, save_tfm_timer_irq_info.p_ildi);
}

// This function will be called by the SPM during initializaiton 
enum tfm_hal_status_t tfm_timer_irq_init(void *p_pt,
                                          struct irq_load_info_t *p_ildi)
{
    save_tfm_timer_irq_info.p_ildi = p_ildi;
    save_tfm_timer_irq_info.p_pt = p_pt;

    NVIC_SetPriority(TFM_TIMER_IRQ, 1);
    NVIC_ClearTargetState(TFM_TIMER_IRQ); // Change the target of the interrupt from NS to S. (default the interrupts are all tagertting NS)
    //NVIC_SetPendingIRQ(TFM_TIMER_IRQ);
    NVIC_DisableIRQ(TFM_TIMER_IRQ);

    return TFM_HAL_SUCCESS;
}