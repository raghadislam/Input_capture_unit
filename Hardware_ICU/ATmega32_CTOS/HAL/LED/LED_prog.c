///*
// * LED_prog.c
// *
// *  Created on: Jul 16, 2023
// *      Author: DeLL
// */
//
//#include "../../SERVICE/STDTypes.h"
//#include "../../SERVICE/errorState.h"
//
//#include "LED_config.h"
//#include "LED_priv.h"
//
//#include "../../MCAL/DIO/DIO_int.h"
//
//
//
//
//ES_t LED_enuInit(LED_t* Copy_pstrLedConfig)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//	if(Copy_pstrLedConfig != NULL)
//	{
//		u8 Local_u8Iterator;
//		for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_LED ; ++Local_u8Iterator)
//		{
//
//			Local_enuErrorState = DIO_enuSetPinDir(Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
//					Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID,
//					DIO_u8OUTPUT );
//
//			if(Local_enuErrorState!= ES_OK) return Local_enuErrorState;
//
//			if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8connection == LED_SINK)
//			{
//				if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_ON)
//				{
//					Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
//							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID,
//							DIO_u8LOW);
//
//				}
//				else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_OFF)
//				{
//					Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
//							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID,
//							DIO_u8HIGH);
//				}
//				else return ES_OUT_OF_RANGE;
//
//			}
//			else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8connection == LED_SORCE)
//			{
//				if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_ON)
//				{
//					Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
//							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID,
//							DIO_u8HIGH);
//
//				}
//				else if(Copy_pstrLedConfig[Local_u8Iterator].LED_u8InitState == LED_OFF)
//				{
//					Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedConfig[Local_u8Iterator].LED_u8PortID,
//							Copy_pstrLedConfig[Local_u8Iterator].LED_u8PinID,
//							DIO_u8LOW);
//				}
//				else return ES_OUT_OF_RANGE;
//
//			}
//			else return ES_OUT_OF_RANGE;
//		}
//	}
//	else Local_enuErrorState = ES_NULL_POINTER;
//
//	return Local_enuErrorState;
//}
//
//
//
//ES_t LED_enuLedTurnON(LED_t* Copy_pstrLedID)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//
//	if(Copy_pstrLedID != NULL )
//	{
//		if(Copy_pstrLedID->LED_u8connection == LED_SINK)
//		{
//
//			Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedID->LED_u8PortID,
//					Copy_pstrLedID->LED_u8PinID,
//					DIO_u8LOW);
//
//		}
//		else if(Copy_pstrLedID->LED_u8connection == LED_SORCE)
//		{
//			Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedID->LED_u8PortID,
//					Copy_pstrLedID->LED_u8PinID,
//					DIO_u8HIGH);
//		}
//	}
//	else return ES_NULL_POINTER;
//
//	return Local_enuErrorState;
//}
//
//
//	ES_t LED_enuLedTurnOFF(LED_t* Copy_pstrLedID)
//	{
//		ES_t Local_enuErrorState = ES_NOK;
//
//		if(Copy_pstrLedID != NULL )
//		{
//			if(Copy_pstrLedID->LED_u8connection == LED_SINK)
//			{
//
//				Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedID->LED_u8PortID,
//						Copy_pstrLedID->LED_u8PinID,
//						DIO_u8HIGH);
//
//			}
//			else if(Copy_pstrLedID->LED_u8connection == LED_SORCE)
//			{
//				Local_enuErrorState = DIO_enuSetPinVal( Copy_pstrLedID->LED_u8PortID,
//						Copy_pstrLedID->LED_u8PinID,
//						DIO_u8LOW);
//			}
//		}
//		else return ES_NULL_POINTER;
//
//		return Local_enuErrorState;
//	}
