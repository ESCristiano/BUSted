#include "cache.h"

void ICache_invalidation(){
    if (READ_BIT(ICACHE->SR, ICACHE_SR_BUSYF) != 0U) {
        return -1;
    }
    else{
        /* Make sure BSYENDF is reset before to start cache invalidation */
        CLEAR_BIT(ICACHE->FCR, ICACHE_FCR_CBSYENDF);

        /* Launch cache invalidation */
        SET_BIT(ICACHE->CR, ICACHE_CR_CACHEINV);

        while (READ_BIT(ICACHE->SR, ICACHE_SR_BSYENDF) == 0U);
    }
    /* Clear BSYENDF */
    WRITE_REG(ICACHE->FCR, ICACHE_FCR_CBSYENDF);
}

void enable_ICache(){
    if (READ_BIT(ICACHE->CR, ICACHE_CR_EN) != 0U) {
            LOG_MSG("Error! I-Cache already enabled\n");
        }
        else {
            SET_BIT(ICACHE->CR, ICACHE_CR_EN);
        }
}
