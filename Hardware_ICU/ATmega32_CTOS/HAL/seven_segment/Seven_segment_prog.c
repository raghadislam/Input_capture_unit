///*
// * Seven_segment_prog.c
// *
// *  Created on: Jul 16, 2023
// *      Author: Raghad Islam
// */
//
//
//#include "../../SERVICE/errorState.h"
//#include "../../SERVICE/STDTypes.h"
//
//
//#include "../../MCAL/DIO/DIO_int.h"
//
//#include "Seven_segment_config.h"
//#include "Seven_segment_priv.h"
//
//
//extern SEG_t SEVSEG_AstrConfig[NUM_OF_SEG];
//extern u8 SEVEN_SEG_Au8Numbers[];
//
//
//ES_t Seven_segment_enuInit(SEG_t* Copy_AstrSegConfig)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//	u8 Local_u8Iterator;
//	if(Copy_AstrSegConfig != NULL)
//	{
//		u32 Local_u32Check;
//
//		for(Local_u8Iterator = 0 ; Local_u8Iterator < NUM_OF_SEG ; ++Local_u8Iterator )
//		{
//			Local_u32Check = 0;
//
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8APort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8APin, DIO_u8OUTPUT))<<0 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8BPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8BPin, DIO_u8OUTPUT))<<3 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CPin, DIO_u8OUTPUT))<<6 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DPin, DIO_u8OUTPUT))<<9 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8EPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8EPin, DIO_u8OUTPUT))<<12);
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8FPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8FPin, DIO_u8OUTPUT))<<15);
//			Local_u32Check |= ((u32)(DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8GPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8GPin, DIO_u8OUTPUT))<<18);
//
//			if(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CMNPort != NOT_CONNECTED && Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CMNPin != NOT_CONNECTED )
//			{
//				Local_enuErrorState = DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CMNPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8CMNPin, DIO_u8OUTPUT);
//			}
//
//			if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//
//			if(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DOTPort != NOT_CONNECTED && Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DOTPin != NOT_CONNECTED )
//			{
//				Local_enuErrorState = DIO_enuSetPinDir(Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DOTPort, Copy_AstrSegConfig[Local_u8Iterator].SEG_u8DOTPin, DIO_u8OUTPUT);
//			}
//
//			if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//
//
//		}
//
////		*((u8*)0x5b) = (Local_u32Check>>18);
////		*((u8*)0x3d) = (Local_u32Check>>8);
////		*((u8*)0x3c) = (Local_u32Check>>16);
//
//
//
//		for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
//		{
//			if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
//			{
//				*((u8*)0x3d)=0;
//				return ES_NOK;
//			}
//		}
//
//	}
//	else return ES_NULL_POINTER;
//
//	return Local_enuErrorState;
//}
//
//
//
//ES_t Seven_segment_enuDisplayNum(u8 Copy_u8SegID, u8 Copy_u8Num)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//	u16 Local_u32Check = 0;
//
//	if(Copy_u8Num < 10 && Copy_u8SegID < NUM_OF_SEG)
//	{
//		if (SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE)
//		{
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>0)&1 ))<<0 );
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>1)&1 ))<<3 );
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>2)&1 ))<<6 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>3)&1 ))<<9 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>4)&1 ))<<12);
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>5)&1 ))<<15);
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPin, (SEVEN_SEG_Au8Numbers[Copy_u8Num]>>6)&1 ))<<18);
//		}
//
//		else if (SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//		{
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>0)&1) ))<<0 );
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>1)&1) ))<<3 );
//			Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>2)&1) ))<<6 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>3)&1) ))<<9 );
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>4)&1) ))<<12);
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>5)&1) ))<<15);
//			Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPin, !((SEVEN_SEG_Au8Numbers[Copy_u8Num]>>6)&1) ))<<18);
//		}
//		else return ES_WRONG_TYPE;
//
//
//	}
//	else return ES_OUT_OF_RANGE;
//
//	u8 Local_u8Iterator;
//	for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
//	{
//		if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
//		{
//			return ES_NOK;
//		}
//	}
//	Local_enuErrorState = ES_OK;
//
//	return Local_enuErrorState;
//
//}
//
//
//ES_t Seven_segment_enuEnableCommon(u8 Copy_u8SegID)
//{
//
//	ES_t Local_enuErrorState = ES_NOK;
//
//	if(Copy_u8SegID < NUM_OF_SEG)
//	{
//
//		if( SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort != NOT_CONNECTED && SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin != NOT_CONNECTED)
//		{
//			if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE )
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin, DIO_u8LOW);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//
//			else if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin, DIO_u8HIGH);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//			else return ES_WRONG_TYPE;
//		}
//
//		else return ES_WRONG_TYPE;
//
//	}
//	else return ES_OUT_OF_RANGE;
//
//	Local_enuErrorState = ES_OK;
//
//	return Local_enuErrorState;
//
//
//}
//
//ES_t Seven_segment_enuDisableCommon(u8 Copy_u8SegID)
//{
//
//	ES_t Local_enuErrorState = ES_NOK;
//
//	if(Copy_u8SegID < NUM_OF_SEG)
//	{
//
//		if( SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort != NOT_CONNECTED && SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin != NOT_CONNECTED)
//		{
//			if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE )
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin, DIO_u8HIGH);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//
//			else if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CMNPin, DIO_u8LOW);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//			else return ES_WRONG_TYPE;
//		}
//
//		else return ES_WRONG_TYPE;
//
//	}
//	else return ES_OUT_OF_RANGE;
//
//	Local_enuErrorState = ES_OK;
//
//	return Local_enuErrorState;
//
//}
//
//ES_t Seven_segment_enuEnableDot(u8 Copy_u8SegID)
//{
//
//	ES_t Local_enuErrorState = ES_NOK;
//
//	if(Copy_u8SegID < NUM_OF_SEG)
//	{
//
//		if( SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort != NOT_CONNECTED && SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin != NOT_CONNECTED)
//		{
//			if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE )
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin, DIO_u8HIGH);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//
//			else if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//			{
//				Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin, DIO_u8LOW);
//
//				if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//			}
//			else return ES_WRONG_TYPE;
//		}
//
//		else return ES_PIN_NOT_CONNECTED;
//	}
//	else return ES_OUT_OF_RANGE;
//
//	Local_enuErrorState = ES_OK;
//
//	return Local_enuErrorState;
//
//
//}
//
//ES_t Seven_segment_enuDisableDot(u8 Copy_u8SegID)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//
//		if(Copy_u8SegID < NUM_OF_SEG)
//		{
//
//			if( SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort != NOT_CONNECTED && SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin != NOT_CONNECTED)
//			{
//				if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE )
//				{
//					Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin, DIO_u8LOW);
//
//					if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//				}
//
//				else if ( SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//				{
//					Local_enuErrorState = DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DOTPin, DIO_u8HIGH);
//
//					if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
//				}
//				else return ES_WRONG_TYPE;
//			}
//
//			else return ES_PIN_NOT_CONNECTED;
//		}
//		else return ES_OUT_OF_RANGE;
//
//		Local_enuErrorState = ES_OK;
//
//		return Local_enuErrorState;
//
//}
//
//ES_t Seven_segment_enuClearDisplay(u8 Copy_u8SegID)
//{
//	ES_t Local_enuErrorState = ES_NOK;
//		u16 Local_u32Check = 0;
//
//		if( Copy_u8SegID < NUM_OF_SEG)
//		{
//			if (SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_CATHODE)
//			{
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APin, DIO_u8LOW ))<<0 );
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPin, DIO_u8LOW ))<<3 );
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPin, DIO_u8LOW ))<<6 );
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPin, DIO_u8LOW ))<<9 );
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPin, DIO_u8LOW ))<<12);
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPin, DIO_u8LOW ))<<15);
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPin, DIO_u8LOW ))<<18);
//			}
//
//			else if (SEVSEG_AstrConfig[Copy_u8SegID].SEG_TYPE == COMMON_ANODE)
//			{
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8APin, DIO_u8HIGH ))<<0 );
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8BPin, DIO_u8HIGH ))<<3 );
//				Local_u32Check |= ((DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8CPin, DIO_u8HIGH ))<<6 );
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8DPin, DIO_u8HIGH ))<<9 );
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8EPin, DIO_u8HIGH ))<<12);
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8FPin, DIO_u8HIGH ))<<15);
//				Local_u32Check |= ((u32)(DIO_enuSetPinVal(SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPort, SEVSEG_AstrConfig[Copy_u8SegID].SEG_u8GPin, DIO_u8HIGH ))<<18);
//			}
//			else return ES_WRONG_TYPE;
//
//
//		}
//		else return ES_OUT_OF_RANGE;
//
//		u8 Local_u8Iterator;
//		for(Local_u8Iterator = 0 ; Local_u8Iterator < 21 ; Local_u8Iterator += 3)
//		{
//			if( ( ( Local_u32Check>>Local_u8Iterator ) &7 ) != ES_OK )
//			{
//				return ES_NOK;
//			}
//		}
//		Local_enuErrorState = ES_OK;
//
//		return Local_enuErrorState;
//}
//
