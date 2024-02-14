/*
 * LED_config.c
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LED_config.h"
#include "LED_priv.h"

LED_t LED_AstrLedConfig [NUM_OF_LED] ={
		{DIO_u8PORTA, DIO_u8PIN5, LED_SINK , LED_OFF },
		{DIO_u8PORTA, DIO_u8PIN3, LED_SORCE, LED_OFF },
		{DIO_u8PORTA, DIO_u8PIN2, LED_SINK , LED_OFF }
};

