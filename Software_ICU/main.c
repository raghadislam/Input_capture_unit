/********************************
 * main.c			*
 *	lab: S/W ICU		*
 *  Created on: Dec 18, 2023	*
 *      Author: Raghad Islam	*
 *				*
 ********************************/
 
 /* -------- includes -------- */
#include <util/delay.h>
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/GIE/GIE_int.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_config.h"
#include "ATmega32_CTOS/MCAL/EXTI/EXTI_int.h"
#include "ATmega32_CTOS/MCAL/TIMER/timer_int.h"

#include "ATmega32_CTOS/HAL/LCD/LCD_int.h"

extern EXTI_t EXTI_AstrEXTIConfig[3];
u16 Global_u8PeriodTicks=0;
u16 Global_u8ONTicks=0;

void ICU_SW();

int main()
{
	DIO_enuInit();

	EXTI_enuInit(EXTI_AstrEXTIConfig);
	EXIT_enuINT0SetCallBack(&ICU_SW);

	TIMER1_enuInit();
	TIMER0_enuInit();
	TIMER_enuSetDutyCycle(TIMER0,25);
	LCD_enuInit();
	GIE_viodEnable();

	while(1)
	{
		/* wait untell we get the readings */
		while((Global_u8PeriodTicks == 0) && (Global_u8ONTicks == 0));
		
		/* print readings on the LCD */
		LCD_enuGoto(1,0);
		LCD_enuWriteNumber(Global_u8PeriodTicks);
		LCD_enuGoto(2,0);
		LCD_enuWriteNumber(Global_u8ONTicks);

	}
	return 0;
}

void ICU_SW()
{
	static u8 local_u8Counter = 0;
	local_u8Counter++;
	if(local_u8Counter == 1)
	{
		/* first rising edge */
		Timer_enuSetTimerVal(TIMER1,0);
	}
	else if(local_u8Counter == 2)
	{
		/* seconed rising edge */

		/* read the period ticks */
		Timer_enuGetTimerVal(TIMER1,&Global_u8PeriodTicks);

		/* change trigger to falling */
		EXTI_enuSetSenseCtrl(EXTI_INT0,FALLING_EDGE);
	}
	else if(local_u8Counter == 3)
	{
		/* get number of ticks in the on time */
		Timer_enuGetTimerVal(TIMER1,&Global_u8ONTicks);
		Global_u8ONTicks -= Global_u8PeriodTicks;

		/* disable external interrupt */
		EXTI_enuIntDisable(EXTI_INT0);

	}
}

