#include "iwdg.h"

void iwdg_init()
{
    /* Enable write access to IWDG_PSR and IWDG_RLDR registers */
    IWDG_Write_Enable(IWDG_WRITEACCESS_ENABLE);

    /* IWDG counter clock: 40KHz(LSI) / 256 = 0.15625 KHz */
    IWDG_SetPrescaler(IWDG_PRESCALER_256);

    /* Set counter reload value to 4094 */
    IWDG_SetReloadValue(800);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable(); 
}

void iwdg_feed()
{
    /* Reload IWDG counter */
    IWDG_ReloadCounter();
}
