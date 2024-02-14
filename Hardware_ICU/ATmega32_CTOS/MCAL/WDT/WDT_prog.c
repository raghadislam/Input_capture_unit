/*
 * WDT_prog.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Raghad Islam
 */
#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"
#include "../../SERVICE/errorState.h"
#include "WDT_priv.h"
#include "WDT_config.h"

/**
 * @brief Function to set the time out period for the Watch Dog timer
 *
 * @param  Copy_u16Time: 1- WDT_16MS
 *                       2- WDT_32MS
 *                       3- WDT_65MS
 *                       4- WDT_130MS
 *                       5- WDT_260MS
 *                       6- WDT_520Ms
 *                       7- WDT_1000MS
 *                       8- WDT_2100MS
 * @return error stet
 */
ES_t WDT_enuSetTimeOut(u16 Copy_u16Time)
{
	ES_t Local_enuErrorState = ES_OK;
	if((Copy_u16Time >= WDT_16MS) && (Copy_u16Time <= WDT_2100MS))
	{
		/* Clear the prescaler bits */
		WDTCR &= WDT_MASK;
		/* Set the required prescaler */
		WDTCR |= Copy_u16Time;
	}
	else Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}


/**
 * @brief Function to enable the Watch Dog timer
 *
 * @param  void
 *
 * @return void
 */
void WDT_vidEnable(void)
{
	Set_bit(WDTCR,WDTCR_WDE);
}

/**
 * @brief Function to disable the Watch Dog timer
 *
 * @param  void
 *
 * @return void
 */
void WDT_vidDisable(void)
{
	/* Write logical one to WDTOE and WDE */
	WDTCR |= 0b00011000;
	/* Turn off WDT */
	Clr_bit(WDTCR,WDTCR_WDE);

}
