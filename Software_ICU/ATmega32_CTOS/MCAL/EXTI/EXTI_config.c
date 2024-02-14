/*
 * EXTI_config.c
 *
 *  Created on: Sep 8, 2023
 *      Author: Raghad Islam
 */
#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"


#include "EXTI_priv.h"
#include "EXTI_config.h"

EXTI_t EXTI_AstrEXTIConfig[3]={

		{ENABLED,RISING_EDGE},
		{DISABLED,FALLING_EDGE},
		{DISABLED,FALLING_EDGE}
};
