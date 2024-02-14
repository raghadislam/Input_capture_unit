/*
 * Switch_prog.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/errorState.h"

#include "Switch_priv.h"
#include "Switch_config.h"

#include "../../MCAL/DIO/DIO_int.h"

ES_t Switch_enuInit(SW_t* Copy_ArrStrSwitchState ){

	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_ArrStrSwitchState != NULL){

	u8 Local_u8Iterator;

	for( Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_SW ; ++Local_u8Iterator)
	{
		Local_enuErrorState = DIO_enuSetPinDir(
				Copy_ArrStrSwitchState[Local_u8Iterator].SW_PortID,
				Copy_ArrStrSwitchState[Local_u8Iterator].SW_PinID ,
				DIO_u8INPUT
		);

		Local_enuErrorState = DIO_enuSetPinVal(
				Copy_ArrStrSwitchState[Local_u8Iterator].SW_PortID,
				Copy_ArrStrSwitchState[Local_u8Iterator].SW_PinID ,
				Copy_ArrStrSwitchState[Local_u8Iterator].SW_Status
		);

		if (Local_enuErrorState != ES_OK) break;

	}
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;

}

ES_t Switch_enuGetState(SW_t* Copy_ArrStrSwitchState , u8* Copy_pu8State){

	ES_t Local_enuErrorState = ES_NOK;

	if( Copy_pu8State != NULL && Copy_ArrStrSwitchState != NULL )
	{
		Local_enuErrorState = DIO_enuGetPinVal(
				Copy_ArrStrSwitchState->SW_PortID,
				Copy_ArrStrSwitchState->SW_PinID ,
				Copy_pu8State
		);
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;

}

