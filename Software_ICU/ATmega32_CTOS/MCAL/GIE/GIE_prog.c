/*
 * GIE_prog.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"

#include "GIE_register.h"

void GIE_viodEnable(void){

	Set_bit(SREG,SREG_I);
}

void GIE_viodDisable(void){

	Clr_bit(SREG,SREG_I);

}
