/*
 * EXTI_prog.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"
#include "../../SERVICE/errorState.h"

#include "EXTI_priv.h"

#include "EXTI_config.h"

// to do : use arry instead
void (*Global_pvEXTI_INT0_ADD)(void) = NULL;
void (*Global_pvEXTI_INT1_ADD)(void) = NULL;
void (*Global_pvEXTI_INT2_ADD)(void) = NULL;





ES_t EXTI_enuInit(EXTI_t * Copy_pstrEXTIConfig)
{

	ES_t Local_u8ErrorState = ES_OK;

	if(Copy_pstrEXTIConfig == NULL) return ES_NULL_POINTER;

	if(Copy_pstrEXTIConfig[0].EXTI_u8State == ENABLED)
	{
		/*set sense control for INT0*/

		switch (Copy_pstrEXTIConfig[0].EXTI_u8Sense)
		{
		case FALLING_EDGE:  Set_bit(MCUCR,MCUCR_ISC01); Clr_bit(MCUCR,MCUCR_ISC00); break;
		case RISING_EDGE :  Set_bit(MCUCR,MCUCR_ISC01); Set_bit(MCUCR,MCUCR_ISC00); break;
		case ON_CHANGE   :  Clr_bit(MCUCR,MCUCR_ISC01); Set_bit(MCUCR,MCUCR_ISC00); break;
		case LOW_LEVEL   :  Clr_bit(MCUCR,MCUCR_ISC01); Clr_bit(MCUCR,MCUCR_ISC00); break;
		default : Local_u8ErrorState = ES_UNSUPPORTED_MODE;
		}

		/*enable  peripheral interrupt for INT0*/

		Set_bit(GICR,GICR_INT0);
	}

	if(Copy_pstrEXTIConfig[1].EXTI_u8State == ENABLED)
	{
		/*set sense control for INT1*/

		switch (Copy_pstrEXTIConfig[1].EXTI_u8Sense)
		{
		case FALLING_EDGE:  Set_bit(MCUCR,MCUCR_ISC11); Clr_bit(MCUCR,MCUCR_ISC10); break;
		case RISING_EDGE :  Set_bit(MCUCR,MCUCR_ISC11); Set_bit(MCUCR,MCUCR_ISC10); break;
		case ON_CHANGE   :  Clr_bit(MCUCR,MCUCR_ISC11); Set_bit(MCUCR,MCUCR_ISC10); break;
		case LOW_LEVEL   :  Clr_bit(MCUCR,MCUCR_ISC11); Clr_bit(MCUCR,MCUCR_ISC10); break;
		default : Local_u8ErrorState = ES_UNSUPPORTED_MODE;
		}

		/*enable  peripheral interrupt for INT1*/

		Set_bit(GICR,GICR_INT1);
	}

	if(Copy_pstrEXTIConfig[2].EXTI_u8State == ENABLED)
	{
		/*set sense control for INT2*/

		switch (Copy_pstrEXTIConfig[2].EXTI_u8Sense)
		{
		case FALLING_EDGE:  Clr_bit(MCUCSR,MCUCSR_ISC2); break;
		case RISING_EDGE :  Set_bit(MCUCSR,MCUCSR_ISC2); break;
		default : Local_u8ErrorState = ES_UNSUPPORTED_MODE;
		}

		/*enable  peripheral interrupt for INT2*/

		Set_bit(GICR,GICR_INT2);
	}

	return Local_u8ErrorState;
}

ES_t EXTI_enuSetSenseCtrl(u8 Copy_u8INTPin, u8 Copy_u8Sense){

		ES_t Local_u8ErrorState = ES_OK;

		if(Copy_u8Sense == LOW_LEVEL)
		{
			switch(Copy_u8INTPin)
			{
			case EXTI_INT0 :

				Clr_bit(MCUCR,MCUCR_ISC00);
				Clr_bit(MCUCR,MCUCR_ISC01);
				break;

			case EXTI_INT1 :

				Clr_bit(MCUCR,MCUCR_ISC11);
				Clr_bit(MCUCR,MCUCR_ISC10);
				break;

			case EXTI_INT2 : Local_u8ErrorState = ES_UNSUPPORTED_MODE;
				break;

			default : Local_u8ErrorState = ES_WEONG_PIN;

			}
		}
		else if(Copy_u8Sense == RISING_EDGE)
		{
			switch(Copy_u8INTPin)
			{
			case EXTI_INT0 :

				Set_bit(MCUCR,MCUCR_ISC01);
				Set_bit(MCUCR,MCUCR_ISC00);
				break;

			case EXTI_INT1 :

				Set_bit(MCUCR,MCUCR_ISC11);
				Set_bit(MCUCR,MCUCR_ISC10);
				break;

			case EXTI_INT2 :

				Set_bit(MCUCSR,MCUCSR_ISC2);
				break;

			default : Local_u8ErrorState = ES_WEONG_PIN;

			}
		}
		else if(Copy_u8Sense == FALLING_EDGE)
		{
			switch(Copy_u8INTPin)
			{
			case EXTI_INT0 :

				Set_bit(MCUCR,MCUCR_ISC01);
				Clr_bit(MCUCR,MCUCR_ISC00);
				break;
			case EXTI_INT1 :

				Set_bit(MCUCR,MCUCR_ISC11);
				Clr_bit(MCUCR,MCUCR_ISC10);
				break;

			case EXTI_INT2 :

				Clr_bit(MCUCSR,MCUCSR_ISC2);
				break;

			default : Local_u8ErrorState = ES_WEONG_PIN;

			}
		}
		else if(Copy_u8Sense == ON_CHANGE)
		{
			switch(Copy_u8INTPin)
			{
			case EXTI_INT0 :

				Clr_bit(MCUCR,MCUCR_ISC01);
				Set_bit(MCUCR,MCUCR_ISC00);
				break;

			case EXTI_INT1 :

				Clr_bit(MCUCR,MCUCR_ISC11);
				Set_bit(MCUCR,MCUCR_ISC10);
				break;

			case EXTI_INT2 :
				Local_u8ErrorState = ES_UNSUPPORTED_MODE;
				break;

			default : Local_u8ErrorState = ES_WEONG_PIN;
			}
		}
		else {
			Local_u8ErrorState = ES_WRONG_TYPE;
		}

		return Local_u8ErrorState;
}




ES_t EXTI_enuIntEnable(u8 Copy_u8INTPin){

	ES_t Local_u8ErrorState = ES_NOK;

	switch(Copy_u8INTPin)
	{
	case EXTI_INT0 :

		Set_bit(GICR,GICR_INT0);
		Local_u8ErrorState = ES_OK;
		break;

	case EXTI_INT1 :

		Set_bit(GICR,GICR_INT1);
		Local_u8ErrorState = ES_OK;
		break;

	case EXTI_INT2 :

		Set_bit(GICR,GICR_INT2);
		Local_u8ErrorState = ES_OK;
		break;

	default : Local_u8ErrorState = ES_WEONG_PIN;
	}

	return Local_u8ErrorState;
}



ES_t EXTI_enuIntDisable(u8 Copy_u8INTPin){

	ES_t Local_u8ErrorState = ES_NOK;

	switch(Copy_u8INTPin)
	{
	case EXTI_INT0 :

		Clr_bit(GICR,GICR_INT0);
		Local_u8ErrorState = ES_OK;
		break;

	case EXTI_INT1 :

		Clr_bit(GICR,GICR_INT1);
		Local_u8ErrorState = ES_OK;
		break;

	case EXTI_INT2 :

		Clr_bit(GICR,GICR_INT2);
		Local_u8ErrorState = ES_OK;
		break;

	default : Local_u8ErrorState = ES_WEONG_PIN;
	}

	return Local_u8ErrorState;

}

ES_t EXIT_enuINT0SetCallBack(void(*Copy_pvUserISR)(void))
{
	ES_t Local_u8ErrorState = ES_NOK;
	if(Copy_pvUserISR != NULL)
	{
		Global_pvEXTI_INT0_ADD = Copy_pvUserISR;
		Local_u8ErrorState = ES_OK;
	}
	else
	{
		Local_u8ErrorState = ES_NULL_POINTER;
	}
	return Local_u8ErrorState;
}

ES_t EXIT_enuINT1SetCallBack(void(*Copy_pvUserISR)(void))
{
	ES_t Local_u8ErrorState = ES_NOK;
	if(Copy_pvUserISR != NULL)
	{
		Global_pvEXTI_INT1_ADD = Copy_pvUserISR;
		Local_u8ErrorState = ES_OK;
	}
	else
	{
		Local_u8ErrorState = ES_NULL_POINTER;
	}
	return Local_u8ErrorState;
}

ES_t EXIT_enuINT2SetCallBack(void(*Copy_pvUserISR)(void))
{
	ES_t Local_u8ErrorState = ES_NOK;
	if(Copy_pvUserISR != NULL)
	{
		Global_pvEXTI_INT2_ADD = Copy_pvUserISR;
		Local_u8ErrorState = ES_OK;
	}
	else
	{
		Local_u8ErrorState = ES_NULL_POINTER;
	}
	return Local_u8ErrorState;
}



/*ISR for INT0*/
void __vector_1(void) __attribute__((signal));

void __vector_1(void){
	if(Global_pvEXTI_INT0_ADD!=NULL) Global_pvEXTI_INT0_ADD();
}


/*ISR for INT1*/
void __vector_2(void) __attribute__((signal));

void __vector_2(void){
	if(Global_pvEXTI_INT1_ADD!=NULL) Global_pvEXTI_INT1_ADD();
}


/*ISR for INT2*/
void __vector_3(void) __attribute__((signal));

void __vector_3(void){
	if(Global_pvEXTI_INT2_ADD!=NULL) Global_pvEXTI_INT2_ADD();
}

