/********************************
 * main.c						*
 *	lab: H/W ICU				*
 *  Created on: Dec 18, 2023	*
 *      Author: Raghad Islam	*
 *								*
 ********************************/

 /* -------- includes -------- */
#include <util/delay.h>
#include "ATmega32_CTOS/SERVICE/STDTypes.h"
#include "ATmega32_CTOS/SERVICE/errorState.h"

#include "ATmega32_CTOS/MCAL/DIO/DIO_int.h"
#include "ATmega32_CTOS/MCAL/GIE/GIE_int.h"

#include "ATmega32_CTOS/MCAL/TIMER/timer_int.h"

#include "ATmega32_CTOS/HAL/LCD/LCD_int.h"


int main()
{
	/* initialize I/O pins */
	DIO_enuInit();
	/* initialize Timer0 to generate the pwm signal */
	TIMER0_enuInit();
	/* initialize Timer1 to analyze the pwm signal */
	TIMER1_enuInit();
	/* initialize the LCD to To display the analyzed signal */
	LCD_enuInit();


	/* generate pwm signal with 25% Duty Cycle from Timer0 and period = 256 micro sec (FASTPWM)*/
	TIMER_enuSetDutyCycle(TIMER0,25);

	/* enable global interrupt */
	GIE_viodEnable();

	/* local variables to hold Duty Cycle and on time */
	u8 Local_u8DutyCycle;
	u16 Local_u16ONTime;
	u16 Local_16Period;

	while(1)
	{

		/*read the duty cycle using hardware ICU */
		ICU_enuGetDutyCycle(&Local_u8DutyCycle);

		/*read the on time using hardware ICU */
		ICU_enuGetOnTime_us(&Local_u16ONTime);

		/*read the period time using hardware ICU */
		ICU_enuGetPeriod_us(&Local_16Period);

		/* print results */
		LCD_enuGoto(1,0);
		LCD_enuWriteNumber(Local_u8DutyCycle);
		LCD_enuGoto(2,0);
		LCD_enuWriteNumber(Local_16Period);
	}
	return 0;
}
