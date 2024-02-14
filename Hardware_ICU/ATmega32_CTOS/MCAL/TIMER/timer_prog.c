/*
 * timer_prog.c
 *
 *  Created on: Dec 18, 2023
 *      Author: Raghad Islam
 */
#include "../../SERVICE/STDTypes.h"
#include "../../SERVICE/BIT_MATH.h"
#include "../../SERVICE/errorState.h"
#include "TIMER_priv.h"
#include "TIMER_config.h"


/*Static variable needed in the ISR of each timer interrupt*/
static u32 Global_u32Timer0Cntr = 0;
static u32 Global_u32Timer1Cntr = 0;
static u32 Global_u32Timer2Cntr = 0;

static u32 Global_u32Timer0Preload = 0;
static u32 Global_u32Timer1Preload = 0;
static u32 Global_u32Timer2Preload = 0;

static u32 Global_u32ReqTimer0Cntr = 1;
static u32 Global_u32ReqTimer1Cntr = 1;
static u32 Global_u32ReqTimer2Cntr = 1;

static u16 Global_u16PeriodTicks1 = 0;
static u16 Global_u16PeriodTicks2 = 0;
static u16 Global_u16ONTicks = 0;

static u8 Global_u8Timer0CTCFlag = 0;
static u8 Global_u8Timer1CTCFlag = 0;
static u8 Global_u8Timer2CTCFlag = 0;

static f32 Global_f32Timer0CTCVal = 0;
static f32 Global_f32Timer1CTCVal = 0;
static f32 Global_f32Timer2CTCVal = 0;

/*---------- prototypes for static functions -----------*/

static void TIMER_VidSetTimer0OVFTime(f32 Copy_f32TimerCtr);
static void TIMER_VidSetTimer1OVFTime(f32 Copy_f32TimerCtr);
static void TIMER_VidSetTimer2OVFTime(f32 Copy_f32TimerCtr);
static void TIMER_VidSetTIMER0CTCTime(f32 Copy_f32TimerCtr);
static void TIMER_VidSetTIMER1CTCTime(f32 Copy_f32TimerCtr);
static void TIMER_VidSetTIMER2CTCTime(f32 Copy_f32TimerCtr);

/*---------------global pointers for ISR---------------*/

static void (*Global_pvTimerCallBackArr[6])(void) = {NULL,NULL,NULL,NULL,NULL,NULL};


/*================== Timer Functions ====================*/

/**
 * @brief functions to initialize timer0 prepheral.
 * @return the error statues.
 */
ES_t TIMER0_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;

	if(TIMER0_STATE == TIMER_ENABLED)
	{
		/*---------------------------initialize the timer0 mode---------------------------*/

		if (TIMER0_MODE == TIMER_MODE_CTC)
		{
			/*set compare match mode*/
			Clr_bit(TCCR0,TCCR0_WGM00);
			Set_bit(TCCR0,TCCR0_WGM01);

			/*output compare match interrupt enable*/
			Set_bit(TIMSK,TIMSK_OCIE0);

			/*set action on OC0 on compare match*/
			if (TIMER0_CTC_ACTION == TOGGLE_OC)
			{
				Set_bit(TCCR0,TCCR0_COM00);
				Clr_bit(TCCR0,TCCR0_COM01);
			}
			else if( TIMER0_CTC_ACTION == CLEAR_OC)
			{
				Clr_bit(TCCR0,TCCR0_COM00);
				Set_bit(TCCR0,TCCR0_COM01);
			}
			else if( TIMER0_CTC_ACTION == SET_OC)
			{
				Set_bit(TCCR0,TCCR0_COM00);
				Set_bit(TCCR0,TCCR0_COM01);
			}
			else if( TIMER0_CTC_ACTION == DISCONNECT_OC)
			{
				Clr_bit(TCCR0,TCCR0_COM00);
				Clr_bit(TCCR0,TCCR0_COM01);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		}
		else if ( TIMER0_MODE == TIMER_MODE_PWM )
		{
			/*set pwm mode*/
			Set_bit(TCCR0,TCCR0_WGM00);
			Clr_bit(TCCR0,TCCR0_WGM01);

			/*choose pwm selectin*/
			if (TIMER0_PWM_SELECTION == CLEAR_ON_UP_SET_ON_DOWN)
			{
				Clr_bit(TCCR0,TCCR0_COM00);
				Set_bit(TCCR0,TCCR0_COM01);
			}
			else if ( TIMER0_PWM_SELECTION == SET_ON_UP_CLEAR_ON_DOWN)
			{
				Set_bit(TCCR0,TCCR0_COM00);
				Set_bit(TCCR0,TCCR0_COM01);
			}
			else if( TIMER0_PWM_SELECTION == OC_DISCONNECTED)
			{
				Clr_bit(TCCR0,TCCR0_COM00);
				Clr_bit(TCCR0,TCCR0_COM01);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;
		}

		else if( TIMER0_MODE == TIMER_MODE_OVE )
		{
			/*set normal mode*/
			Clr_bit(TCCR0,TCCR0_WGM00);
			Clr_bit(TCCR0,TCCR0_WGM01);

			/*Overflow Interrupt Enable*/
			Set_bit(TIMSK,TIMSK_TOIE0);
		}

		else if (TIMER0_MODE == TIMER_MODE_FASTPWM)
		{
			/*set fast pwm mode*/
			Set_bit(TCCR0,TCCR0_WGM00);
			Set_bit(TCCR0,TCCR0_WGM01);

			/*choose fast pwm selectin*/
			if( TIMER0_FASTPWM_SELECTION == CLEAR_ON_COMP_SET_ON_TOP)
			{
				Set_bit(TCCR0,TCCR0_COM01);
				Clr_bit(TCCR0,TCCR0_COM00);
			}
			else if( TIMER0_FASTPWM_SELECTION == SET_ON_COMP_CLEAR_ON_TOP)
			{
				Set_bit(TCCR0,TCCR0_COM00);
				Set_bit(TCCR0,TCCR0_COM01);
			}
			else if( TIMER0_FASTPWM_SELECTION == OC_DISCONNECTED)
			{
				Clr_bit(TCCR0,TCCR0_COM00);
				Clr_bit(TCCR0,TCCR0_COM01);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		/*---------------------------set timer prescaler---------------------------*/

		if (TIMER0_PRESCALER == TIMER_PRESCALER_8)
		{
			Clr_bit(TCCR0,TCCR0_CS00);
			Set_bit(TCCR0,TCCR0_CS01);
			Clr_bit(TCCR0,TCCR0_CS02);
		}

		else if (TIMER0_PRESCALER == TIMER_NO_PRESCALER)
		{
			Set_bit(TCCR0,TCCR0_CS00);
			Clr_bit(TCCR0,TCCR0_CS01);
			Clr_bit(TCCR0,TCCR0_CS02);
		}

		else if (TIMER0_PRESCALER == TIMER_PRESCALER_64)
		{
			Set_bit(TCCR0,TCCR0_CS00);
			Set_bit(TCCR0,TCCR0_CS01);
			Clr_bit(TCCR0,TCCR0_CS02);
		}

		else if (TIMER0_PRESCALER == TIMER_PRESCALER_256)
		{
			Clr_bit(TCCR0,TCCR0_CS00);
			Clr_bit(TCCR0,TCCR0_CS01);
			Set_bit(TCCR0,TCCR0_CS02);
		}

		else if (TIMER0_PRESCALER == TIMER_PRESCALER_1024)
		{
			Set_bit(TCCR0,TCCR0_CS00);
			Clr_bit(TCCR0,TCCR0_CS01);
			Set_bit(TCCR0,TCCR0_CS02);
		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;
	}
	else
	{
		Clr_bit(TCCR0,TCCR0_CS00);
		Clr_bit(TCCR0,TCCR0_CS01);
		Clr_bit(TCCR0,TCCR0_CS02);
	}

	return Local_enuErrorState;
}


/**
 * @brief functions to initialize timer1 prepheral.
 * @return the error statues.
 */
ES_t TIMER1_enuInit()
{

	ES_t Local_enuErrorState = ES_OK;

	/*---------------------------initialize the timer mode---------------------------*/

	if((TIMER1_STATE_A == TIMER_ENABLED) || (TIMER1_STATE_B == TIMER_ENABLED) )
	{
		if	(TIMER1_MODE == TIMER_MODE_OVE)
		{
			/*set overflow mode*/
			Clr_bit(TCCR1A,TCCR1A_WGM10);
			Clr_bit(TCCR1A,TCCR1A_WGM11);
			Clr_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);


			/*enable overflow interrupt*/
			Set_bit(TIMSK,TIMSK_TOIE1);
		}
		else if(TIMER1_MODE == TIMER_MODE_CTC)
		{
			/*set compare match mode*/
			Clr_bit(TCCR1A,TCCR1A_WGM10);
			Clr_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);

			if(TIMER1_CTC_STATE_A == TIMER_ENABLED)
			{
				/*set action on OC1A on compare match*/
				switch(TIMER1_CTC_ACTION)
				{
				case TOGGLE_OC:
					Set_bit(TCCR1A,TCCR1A_COM1A0);
					Clr_bit(TCCR1A,TCCR1A_COM1A1);
					break;
				case CLEAR_OC:
					Clr_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
					break;
				case SET_OC:
					Set_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
					break;
				case DISCONNECT_OC:
					Clr_bit(TCCR1A,TCCR1A_COM1A0);
					Clr_bit(TCCR1A,TCCR1A_COM1A1);
					break;
				default: Local_enuErrorState = ES_UNSUPPORTED_MODE;

				}
				/*enable compare match interrupt*/
				Set_bit(TIMSK,TIMSK_OCIE1A);
			}

			if(TIMER1_CTC_STATE_B == TIMER_ENABLED)
			{
				/*set action on OC1A on compare match*/
				switch(TIMER1_CTC_ACTION)
				{
				case TOGGLE_OC:
					Set_bit(TCCR1A,TCCR1A_COM1B0);
					Clr_bit(TCCR1A,TCCR1A_COM1B1);
					break;
				case CLEAR_OC:
					Clr_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
					break;
				case SET_OC:
					Set_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
					break;
				case DISCONNECT_OC:
					Clr_bit(TCCR1A,TCCR1A_COM1B0);
					Clr_bit(TCCR1A,TCCR1A_COM1B1);
					break;
				default: Local_enuErrorState = ES_UNSUPPORTED_MODE;

				}
				/*enable compare match interrupt*/
				Set_bit(TIMSK,TIMSK_OCIE1B);
			}

		}
		// to do : adjust the COM1A0/COM1A1/COM1B0/COM1B1 for the rest of the modes
		else if(TIMER1_MODE == TIMER_MODE_PWM)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Clr_bit(TCCR1B,TCCR1B_WGM12);
			Set_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_FASTPWM_ICR1)
		{
			Clr_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Set_bit(TCCR1B,TCCR1B_WGM13);
		}

		else if(TIMER1_MODE == TIMER_MODE_FASTPWM_OCRA1)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Set_bit(TCCR1B,TCCR1B_WGM13);
		}

		else if(TIMER1_MODE == TIMER_MODE_PWM_8BIT)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Clr_bit(TCCR1A,TCCR1A_WGM11);
			Clr_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_PWM_9BIT)
		{
			Clr_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Clr_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_PWM_10BIT)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Clr_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_FAST_PWM_8BIT)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Clr_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_FAST_PWM_9BIT)
		{
			Clr_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else if(TIMER1_MODE == TIMER_MODE_FAST_PWM_10BIT)
		{
			Set_bit(TCCR1A,TCCR1A_WGM10);
			Set_bit(TCCR1A,TCCR1A_WGM11);
			Set_bit(TCCR1B,TCCR1B_WGM12);
			Clr_bit(TCCR1B,TCCR1B_WGM13);
		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		/*------------- adjust inverting / noninverting mode in case of FAST PWM mode-------------*/

		if((TIMER1_MODE >= TIMER_MODE_FASTPWM) && (TIMER1_MODE <= TIMER_MODE_FASTPWM_OCRA1))
		{
			if(TIMER1_FASTPWM_STATE_A == TIMER_ENABLED )
			{
				if(TIMER1_FASTPWM_SELECTION_A == CLEAR_ON_COMP_SET_ON_TOP)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
				}
				else if(TIMER1_FASTPWM_SELECTION_A == SET_ON_COMP_CLEAR_ON_TOP)
				{
					Set_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}

			if(TIMER1_FASTPWM_STATE_B == TIMER_ENABLED )
			{
				if(TIMER1_FASTPWM_SELECTION_B == CLEAR_ON_COMP_SET_ON_TOP)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
				}
				else if(TIMER1_FASTPWM_SELECTION_B == SET_ON_COMP_CLEAR_ON_TOP)
				{
					Set_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}
		}


		/*------------- adjust inverting / noninverting mode in case of PWM mode-------------*/

		if((TIMER1_MODE >= TIMER_MODE_PWM) && (TIMER1_MODE <= TIMER_MODE_PWM_10BIT))
		{
			if(TIMER1_PWM_STATE_A == TIMER_ENABLED )
			{
				if(TIMER1_PWM_SELECTION_A == CLEAR_ON_UP_SET_ON_DOWN)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
				}
				else if(TIMER1_FASTPWM_SELECTION_A == SET_ON_UP_CLEAR_ON_DOWN)
				{
					Set_bit(TCCR1A,TCCR1A_COM1A0);
					Set_bit(TCCR1A,TCCR1A_COM1A1);
				}
				else if(TIMER1_PWM_SELECTION_A == OC_DISCONNECTED)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1A0);
					Clr_bit(TCCR1A,TCCR1A_COM1A1);
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}

			if(TIMER1_PWM_STATE_B == TIMER_ENABLED )
			{
				if(TIMER1_PWM_SELECTION_B == CLEAR_ON_UP_SET_ON_DOWN)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
				}
				else if(TIMER1_PWM_SELECTION_B == SET_ON_UP_CLEAR_ON_DOWN)
				{
					Set_bit(TCCR1A,TCCR1A_COM1B0);
					Set_bit(TCCR1A,TCCR1A_COM1B1);
				}
				else if(TIMER1_PWM_SELECTION_B == OC_DISCONNECTED)
				{
					Clr_bit(TCCR1A,TCCR1A_COM1B0);
					Clr_bit(TCCR1A,TCCR1A_COM1B1);
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}
		}

		/*---------------------------set timer prescaler---------------------------*/


		if( TIMER1_PRESCALER == TIMER_NO_PRESCALER)
		{
			Set_bit(TCCR1B,TCCR1B_CS10);
			Clr_bit(TCCR1B,TCCR1B_CS11);
			Clr_bit(TCCR1B,TCCR1B_CS12);
		}

		else if(TIMER1_PRESCALER == TIMER_PRESCALER_8)
		{
			Clr_bit(TCCR1B,TCCR1B_CS10);
			Set_bit(TCCR1B,TCCR1B_CS11);
			Clr_bit(TCCR1B,TCCR1B_CS12);

		}

		else if( TIMER1_PRESCALER == TIMER_PRESCALER_64)
		{
			Set_bit(TCCR1B,TCCR1B_CS10);
			Set_bit(TCCR1B,TCCR1B_CS11);
			Clr_bit(TCCR1B,TCCR1B_CS12);
		}

		else if( TIMER1_PRESCALER == TIMER_PRESCALER_256)
		{
			Clr_bit(TCCR1B,TCCR1B_CS10);
			Clr_bit(TCCR1B,TCCR1B_CS11);
			Set_bit(TCCR1B,TCCR1B_CS12);
		}

		else if( TIMER1_PRESCALER == TIMER_PRESCALER_1024)
		{
			Set_bit(TCCR1B,TCCR1B_CS10);
			Clr_bit(TCCR1B,TCCR1B_CS11);
			Set_bit(TCCR1B,TCCR1B_CS12);
		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		/*---------------------------initialize the ICU mode---------------------------*/
		if(ICU_STATE == TIMER_ENABLED)
		{
			/*set input capture trigger source*/
			switch(ICU_TRIGGER)
			{
			case RISING_EDGE:
				Set_bit(TCCR1B,TCCR1B_ICES1);
				break;
			case FALLING_EDGE:
				Clr_bit(TCCR1B,TCCR1B_ICES1);
				break;
			default:
				Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}

			/*enable input capture interrupt*/
			Set_bit(TIMSK,TIMSK_TICIE1);
		}
	}
	else
	{
		Clr_bit(TCCR1B,TCCR1B_CS10);
		Clr_bit(TCCR1B,TCCR1B_CS11);
		Clr_bit(TCCR1B,TCCR1B_CS12);
	}

	return Local_enuErrorState;
}


/**
 * @brief functions to initialize timer2 prepheral.
 * @return the error statues.
 */
ES_t TIMER2_enuInit()
{
	ES_t Local_enuErrorState = ES_OK;

	if(TIMER2_STATE == TIMER_ENABLED)
	{
		/*---------------------------initialize the timer0 mode---------------------------*/

		if (TIMER2_MODE == TIMER_MODE_CTC)
		{
			/*set compare match mode*/
			Clr_bit(TCCR2,TCCR2_WGM20);
			Set_bit(TCCR2,TCCR2_WGM21);

			/*output compare match interrupt enable*/
			Set_bit(TIMSK,TIMSK_OCIE2);

			/*set action on OC0 on compare match*/
			if (TIMER2_CTC_ACTION == TOGGLE_OC)
			{
				Set_bit(TCCR2,TCCR2_COM20);
				Clr_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_CTC_ACTION == CLEAR_OC)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_CTC_ACTION == SET_OC)
			{
				Set_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_CTC_ACTION == DISCONNECT_OC)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Clr_bit(TCCR2,TCCR2_COM21);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		}
		else if ( TIMER2_MODE == TIMER_MODE_PWM )
		{
			/*set pwm mode*/
			Set_bit(TCCR2,TCCR2_WGM20);
			Clr_bit(TCCR2,TCCR2_WGM21);

			/*choose pwm selectin*/
			if (TIMER2_PWM_SELECTION == CLEAR_ON_UP_SET_ON_DOWN)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if ( TIMER2_PWM_SELECTION == SET_ON_UP_CLEAR_ON_DOWN)
			{
				Set_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_PWM_SELECTION == OC_DISCONNECTED)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Clr_bit(TCCR2,TCCR2_COM21);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;
		}

		else if( TIMER2_MODE == TIMER_MODE_OVE )
		{
			/*set normal mode*/
			Clr_bit(TCCR2,TCCR2_WGM20);
			Clr_bit(TCCR2,TCCR2_WGM21);

			/*Overflow Interrupt Enable*/
			Set_bit(TIMSK,TIMSK_TOIE2);
		}

		else if (TIMER2_MODE == TIMER_MODE_FASTPWM)
		{
			/*set fast pwm mode*/
			Set_bit(TCCR2,TCCR2_WGM20);
			Set_bit(TCCR2,TCCR2_WGM21);

			/*choose fast pwm selectin*/
			if( TIMER2_FASTPWM_SELECTION == CLEAR_ON_COMP_SET_ON_TOP)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_FASTPWM_SELECTION == SET_ON_COMP_CLEAR_ON_TOP)
			{
				Set_bit(TCCR2,TCCR2_COM20);
				Set_bit(TCCR2,TCCR2_COM21);
			}
			else if( TIMER2_FASTPWM_SELECTION == OC_DISCONNECTED)
			{
				Clr_bit(TCCR2,TCCR2_COM20);
				Clr_bit(TCCR2,TCCR2_COM21);
			}
			else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;

		/*---------------------------set timer prescaler---------------------------*/

		if (TIMER2_PRESCALER == TIMER_PRESCALER_8)
		{
			Clr_bit(TCCR2,TCCR2_CS20);
			Set_bit(TCCR2,TCCR2_CS21);
			Clr_bit(TCCR2,TCCR2_CS22);
		}

		else if (TIMER2_PRESCALER == TIMER_NO_PRESCALER)
		{
			Set_bit(TCCR2,TCCR2_CS20);
			Clr_bit(TCCR2,TCCR2_CS21);
			Clr_bit(TCCR2,TCCR2_CS22);
		}

		else if (TIMER2_PRESCALER == TIMER_PRESCALER_64)
		{
			Clr_bit(TCCR2,TCCR2_CS20);
			Clr_bit(TCCR2,TCCR2_CS21);
			Set_bit(TCCR2,TCCR2_CS22);
		}

		else if (TIMER2_PRESCALER == TIMER_PRESCALER_128)
		{
			Set_bit(TCCR2,TCCR2_CS20);
			Clr_bit(TCCR2,TCCR2_CS21);
			Set_bit(TCCR2,TCCR2_CS22);
		}

		else if (TIMER2_PRESCALER == TIMER_PRESCALER_256)
		{
			Clr_bit(TCCR2,TCCR2_CS20);
			Set_bit(TCCR2,TCCR2_CS21);
			Set_bit(TCCR2,TCCR2_CS22);
		}

		else if (TIMER2_PRESCALER == TIMER_PRESCALER_1024)
		{
			Set_bit(TCCR2,TCCR2_CS20);
			Set_bit(TCCR2,TCCR2_CS21);
			Set_bit(TCCR2,TCCR2_CS22);
		}
		else Local_enuErrorState = ES_UNSUPPORTED_MODE;
	}
	else
	{
		Clr_bit(TCCR2,TCCR2_CS20);
		Clr_bit(TCCR2,TCCR2_CS21);
		Clr_bit(TCCR2,TCCR2_CS22);
	}

	return Local_enuErrorState;
}


/**
 * @brief function to disable a specific timer prepheral.
 * @param[in] TIMER id:  	  1- TIMER0
 *                            2- TIMER1
 *                            3- TIMER2
 * @return the error statues.
 */
ES_t TIMER_enuDisable(u8 Copy_u8TimerId)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_u8TimerId)
	{
	case TIMER0:
		Clr_bit(TCCR0,TCCR0_CS00);
		Clr_bit(TCCR0,TCCR0_CS01);
		Clr_bit(TCCR0,TCCR0_CS02);
		break;
	case TIMER1:
		Clr_bit(TCCR1B,TCCR1B_CS10);
		Clr_bit(TCCR1B,TCCR1B_CS11);
		Clr_bit(TCCR1B,TCCR1B_CS12);
		break;
	case TIMER2:
		Clr_bit(TCCR2,TCCR2_CS20);
		Clr_bit(TCCR2,TCCR2_CS21);
		Clr_bit(TCCR2,TCCR2_CS22);
		break;
	default:
		Local_enuErrorState = ES_WRONG_TYPE;
	}
	return Local_enuErrorState;

}


/**
 * @brief function to set the preload value of a specific timer prepheral for post build.
 * @param[in] Copy_u8TimerId:  	1- TIMER0
 *                           	2- TIMER1A
 *                            	3- TIMER1B
 *                            	4- TIMER2
 * @param[in]  Copu_u16Val:  setting Value.
 * @return the error statues.
 */
ES_t Timer_enuSetTimerVal(u8 Copy_TimerId, u16 Copu_u16Val)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_TimerId)
	{
	case TIMER0:
		if(Copu_u16Val < TIMER0_MAX)
		{
			TCNT0 = (u8)Copu_u16Val;
		}
		else Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	case TIMER1:
		if(Copu_u16Val < TIMER1_MAX)
		{
			TCNT1 = Copu_u16Val;
		}
		else Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	case TIMER2:
		if(Copu_u16Val < TIMER2_MAX)
		{
			TCNT2 = (u8)Copu_u16Val;
		}
		else Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	default: Local_enuErrorState = ES_OUT_OF_RANGE;

	}
	return Local_enuErrorState;
}


/**
 * @brief function to get the value of a specific timer prepheral for post build.
 * @param[in] Copu_u16Val:  	 1- TIMER0
 *                           	 2- TIMER1A
 *                            	 3- TIMER1B
 *                           	 4- TIMER2
 * @param[out] Copu_u16Val : Timer reading.
 * @return the error statues.
 */
ES_t Timer_enuGetTimerVal(u8 Copy_TimerId, u16* Copu_u16Val)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copu_u16Val != NULL){

		switch(Copy_TimerId)
		{
		case TIMER0:
			*Copu_u16Val = TCNT0;
			break;
		case TIMER1:
			*Copu_u16Val = TCNT1;
			break;
		case TIMER2:
			*Copu_u16Val = TCNT2;
			break;
		default: Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}


/**
 * @brief function to set the Compare Match value of a specific timer prepheral for post build.
 * @param[in] Copu_u16Val:  	1- TIMER0
 *                            	2- TIMER1A
 *                            	3- TIMER1B
 *                            	4- TIMER2
 * @param[in] Compare Match Value.
 * @return the error statues.
 */
ES_t TIMER_enuSetCompareMatchVAl(u8 Copy_u8TimerID, u16 Copy_u16Val)
{
	ES_t Local_enuErrorState = ES_OK;
	switch(Copy_u8TimerID)
	{
	case TIMER0:
		if(Copy_u16Val < TIMER0_MAX)
		{
			OCR0 =  Copy_u16Val;
		}
		else Local_enuErrorState = ES_NOK;
		break;
	case TIMER1A:
		if(Copy_u16Val < TIMER1_MAX)
		{
			OCR1A =  Copy_u16Val;
		}
		else Local_enuErrorState = ES_NOK;
		break;
	case TIMER1B:
		if(Copy_u16Val < TIMER1_MAX)
		{
			OCR1B =  Copy_u16Val;
		}
		else Local_enuErrorState = ES_NOK;
		break;
	case TIMER2:
		if(Copy_u16Val < TIMER2_MAX)
		{
			OCR2 =  Copy_u16Val;
		}
		else Local_enuErrorState = ES_NOK;
		break;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to set the desired time for the chosen timer prepheral.
 * @param[in] Copy_u8TimerId:	1- TIMER0
 *                           	2- TIMER1A
 *                           	3- TIMER1B
 *                           	4- TIMER2
 *@param[in] Copy_u32Time_us: required time in microseconed.
 * @return the error statues.
 */
ES_t TIMER_enuSetDesiredTime_us(u8 Copy_u8TimerId, f32 Copy_u32Time_us)
{

	ES_t Local_enuErrorState = ES_OK;
	f32 Local_f32NumOfOverflows;
	switch(Copy_u8TimerId)
	{
	case TIMER0:
		Local_f32NumOfOverflows = ((f32)Copy_u32Time_us / TIMER0_TOVF);

		if(TIMER0_MODE == TIMER_MODE_CTC)
		{
			TIMER_VidSetTIMER0CTCTime(Local_f32NumOfOverflows);
		}
		else if(TIMER0_MODE == TIMER_MODE_OVE)
		{
			TIMER_VidSetTimer0OVFTime(Local_f32NumOfOverflows);

		}
		else Local_enuErrorState = ES_NOK;
		break;
	case TIMER1:

		Copy_u32Time_us*=2;
		Local_f32NumOfOverflows = ((f32)Copy_u32Time_us / TIMER1_TOVF);
		if(TIMER1_MODE == TIMER_MODE_CTC)
		{
			TIMER_VidSetTIMER1CTCTime(Local_f32NumOfOverflows);
		}
		else if(TIMER1_MODE == TIMER_MODE_OVE)
		{
			TIMER_VidSetTimer1OVFTime(Local_f32NumOfOverflows);
		}
		else Local_enuErrorState = ES_NOK;
		break;
	case TIMER2:
		Local_f32NumOfOverflows = Copy_u32Time_us / TIMER2_TOVF;
		if(TIMER2_MODE == TIMER_MODE_CTC)
		{
			TIMER_VidSetTIMER2CTCTime(Local_f32NumOfOverflows);
		}
		else if(TIMER2_MODE == TIMER_MODE_OVE)
		{
			TIMER_VidSetTimer2OVFTime(Local_f32NumOfOverflows);
		}
		else Local_enuErrorState = ES_NOK;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to set the desired Duty cycle of the PWM signal for the chosen timer prepheral.
 * @param[in] TIMER id:  	  1- TIMER0
 *                            2- TIMER1A
 *                            3- TIMER1B
 *                            4- TIMER2
 * @param[in] Copy_u8DutyCycle: Duty Cycle value between 0 to 100.
 * @return the error statues.
 */
ES_t TIMER_enuSetDutyCycle(u8 Copy_u8TimerID, u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_u8DutyCycle >= 0) && (Copy_u8DutyCycle <= 100) )
	{
		switch(Copy_u8TimerID)
		{
		case TIMER0:
			if(TIMER0_MODE == TIMER_MODE_FASTPWM)
			{
				if(TIMER0_FASTPWM_SELECTION == CLEAR_ON_COMP_SET_ON_TOP)     /* non-inverted */
				{
					if(Copy_u8DutyCycle == 100)
					{
						OCR0 = 255;
					}
					else
						OCR0 = ((Copy_u8DutyCycle * (TIMER0_MAX)) / 100ULL) ; // momken akteb de bas mn 3'er el shart lw msh hasta5dem el timer 3shan awafar
				}
				else if(TIMER0_FASTPWM_SELECTION == SET_ON_COMP_CLEAR_ON_TOP) /* inverted */
				{
					if(Copy_u8DutyCycle == 0)
					{
						OCR0 = 255;
					}
					else
						OCR0 = ((TIMER0_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}
			else if (TIMER0_MODE == TIMER_MODE_PWM)
			{
				if(TIMER0_PWM_SELECTION == CLEAR_ON_UP_SET_ON_DOWN)     /* non-inverted */
				{
					if(Copy_u8DutyCycle == 100)
					{
						OCR0 = 255;
					}
					else
						OCR0 = ((Copy_u8DutyCycle * (TIMER0_MAX)) / 100ULL) ;
				}
				else if(TIMER0_PWM_SELECTION == SET_ON_UP_CLEAR_ON_DOWN) /* inverted */
				{
					if(Copy_u8DutyCycle == 0)
					{
						OCR0 = 255;
					}
					else
						OCR0 = ((TIMER0_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
				}
				else Local_enuErrorState = ES_UNSUPPORTED_MODE;
			}
			break;
		case TIMER1A:
			if(TIMER1_MODE == TIMER_MODE_FASTPWM)
			{
				if(TIMER1_FASTPWM_STATE_A == TIMER_ENABLED)
				{
					if(TIMER1_FASTPWM_SELECTION_A == CLEAR_ON_COMP_SET_ON_TOP)     /* non-inverted */
					{
						if(Copy_u8DutyCycle == 100)
						{
							OCR1A = 65535;
						}
						else
							OCR1A = ((Copy_u8DutyCycle * (TIMER1_MAX)) / 100) ;
					}
					else if(TIMER1_FASTPWM_SELECTION_A == SET_ON_COMP_CLEAR_ON_TOP) /* inverted */
					{
						if(Copy_u8DutyCycle == 0)
						{
							OCR1A = 65535;
						}
						else
							OCR1A = ((TIMER1_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
					}
					else Local_enuErrorState = ES_UNSUPPORTED_MODE;
				}
			}
			else if (TIMER1_MODE == TIMER_MODE_PWM)
			{
				if(TIMER1_PWM_STATE_A == TIMER_ENABLED)
				{
					if(TIMER1_PWM_SELECTION_A == CLEAR_ON_UP_SET_ON_DOWN)     /* non-inverted */
					{
						if(Copy_u8DutyCycle == 100)
						{
							OCR1A = 65535;
						}
						else
							OCR1A = ((Copy_u8DutyCycle * (TIMER1_MAX)) / 100) ;
					}
					else if(TIMER1_PWM_SELECTION_A == SET_ON_UP_CLEAR_ON_DOWN) /* inverted */
					{
						if(Copy_u8DutyCycle == 0)
						{
							OCR1A = 65535;
						}
						else
							OCR1A = ((TIMER1_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
					}
					else Local_enuErrorState = ES_UNSUPPORTED_MODE;
				}
			}
			break;
		case TIMER1B:
			if(TIMER1_MODE == TIMER_MODE_FASTPWM)
			{
				if(TIMER1_FASTPWM_STATE_B == TIMER_ENABLED){
					if(TIMER1_FASTPWM_SELECTION_B == CLEAR_ON_COMP_SET_ON_TOP)     /* non-inverted */
					{
						if(Copy_u8DutyCycle == 100)
						{
							OCR1B = 65535;
						}
						else
							OCR1B = ((Copy_u8DutyCycle * (TIMER1_MAX)) / 100) ;
					}
					else if(TIMER1_FASTPWM_SELECTION_B == SET_ON_COMP_CLEAR_ON_TOP) /* inverted */
					{
						if(Copy_u8DutyCycle == 0)
						{
							OCR1B = 65535;
						}
						else
							OCR1B = ((TIMER1_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
					}
					else Local_enuErrorState = ES_UNSUPPORTED_MODE;
				}
			}
			else if (TIMER1_MODE == TIMER_MODE_PWM)
			{
				if(TIMER1_PWM_STATE_B == TIMER_ENABLED){
					if(TIMER1_PWM_SELECTION_B == CLEAR_ON_UP_SET_ON_DOWN)     /* non-inverted */
					{
						if(Copy_u8DutyCycle == 100)
						{
							OCR1B = 65535;
						}
						else
							OCR1B = ((Copy_u8DutyCycle * (TIMER1_MAX)) / 100) ;
					}
					else if(TIMER1_PWM_SELECTION_B == SET_ON_UP_CLEAR_ON_DOWN) /* inverted */
					{
						if(Copy_u8DutyCycle == 0)
						{
							OCR1B = 65535;
						}
						else
							OCR1B = ((TIMER1_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
					}
					else Local_enuErrorState = ES_UNSUPPORTED_MODE;
				}
			}
			break;
		case TIMER2:
			if(TIMER2_MODE == TIMER_MODE_FASTPWM)
			{
				if(TIMER2_FASTPWM_SELECTION == CLEAR_ON_COMP_SET_ON_TOP)     /* non-inverted */
				{
					if(Copy_u8DutyCycle == 100)
					{
						OCR2 = 255;
					}
					else
						OCR2 = ((Copy_u8DutyCycle * (TIMER2_MAX)) / 100) ;
				}
				else if(TIMER2_FASTPWM_SELECTION == SET_ON_COMP_CLEAR_ON_TOP) /* inverted */
				{
					if(Copy_u8DutyCycle == 0)
					{
						OCR2 = 255;
					}
					else
						OCR2 = ((TIMER2_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
				}
			}
			else if (TIMER2_MODE == TIMER_MODE_PWM)
			{
				if(TIMER2_PWM_SELECTION == CLEAR_ON_UP_SET_ON_DOWN)     /* non-inverted */
				{
					if(Copy_u8DutyCycle == 100)
					{
						OCR2 = 255;
					}
					else
						OCR2 = ((Copy_u8DutyCycle * (TIMER2_MAX)) / 100) ;
				}
				else if(TIMER2_PWM_SELECTION == SET_ON_UP_CLEAR_ON_DOWN) /* inverted */
				{
					if(Copy_u8DutyCycle == 0)
					{
						OCR2 = 255;
					}
					else
						OCR2 = ((TIMER2_MAX) * (100 - Copy_u8DutyCycle)) / 100 ;
				}
			}
			break;
		default: Local_enuErrorState = ES_WRONG_TYPE;

		}
	}
	else Local_enuErrorState = ES_OUT_OF_RANGE;

	return Local_enuErrorState;
}


/**
 * @brief function to Get the period time for a signal using ICU.
 * @param[out] Copy_u16Period: the period of the signal
 * @return the error statues.
 */
ES_t ICU_enuGetPeriod_us(u16* Copy_u16Period)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_u16Period != NULL)
	{
		*Copy_u16Period = ((Global_u16PeriodTicks2-Global_u16PeriodTicks1)*1000000ULL*TIMER1_PRESCALER)/SYSTEM_CLK;
	}
	else Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}


/**
 * @brief function to Get the on time for a signal using ICU.
 * @param[out] Copy_u16OnTime: the on time of the signal
 * @return the error statues.
 */
ES_t ICU_enuGetOnTime_us(u16* Copy_u16OnTime)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_u16OnTime != NULL)
	{
		*Copy_u16OnTime = ((Global_u16ONTicks)*1000000ULL*TIMER1_PRESCALER)/SYSTEM_CLK;
	}
	else Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}


/**
 * @brief function to Get the Duty Cycle for a signal using ICU.
 * @param[out] Copy_u8DutyCycle: the Duty Cycle of the signal
 * @return the error statues.
 */
ES_t ICU_enuGetDutyCycle(u8* Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_u8DutyCycle != NULL)
	{
		*Copy_u8DutyCycle = (Global_u16ONTicks * 100) / (Global_u16PeriodTicks2-Global_u16PeriodTicks1) ;
	}
	else Local_enuErrorState = ES_NULL_POINTER;
	return Local_enuErrorState;
}


/**
 * @brief function to cahnge the Trigger Edge for the ICU in timer 1.
 * @param[in] trigger edge:   1- ICU_RISING_EDGE
 *                            2- ICU_FALLING_EDGE
 * @return the error statues.
 */
ES_t ICU_enuSetTriggerEdge(u8 Copy_u8TRiggerEdge)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8TRiggerEdge)
	{
	case RISING_EDGE:
		Set_bit(TCCR1B,TCCR1B_ICES1);
		break;
	case FALLING_EDGE:
		Clr_bit(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		Local_enuErrorState = ES_UNSUPPORTED_MODE;
	}

	return Local_enuErrorState;
}


/**
 * @brief void function to Disable ICU Interrupt.
 */
void ICU_vidEnableInterrupt()
{
	Set_bit(TIMSK,TIMSK_TICIE1);
}


/**
 * @brief void function to Enable ICU Interrupt.
 */
void ICU_vidDisableInterrupt()
{
	Clr_bit(TIMSK,TIMSK_TICIE1);
}


/**
 * @brief function to get the value of a the input capture register (ICR1).
 * @param[out] input capture register reading.
 * @return the error statues.
 */
ES_t ICU_enuGetInputCapture(u16* Copy_pu16InputCapture)
{
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_pu16InputCapture != NULL)
	{
		*Copy_pu16InputCapture = ICR1;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


/**
 * @brief function to receive the addresse of the ISR function of a specific timer prepheral.
 * @param[in] TIMER id:  	  1- TIMER0
 * 							  2- TIMER1  (overflow)
 *                            2- TIMER1A (CTC A)
 *                            3- TIMER1B (CTC B)
 *                            4- TIMER2
 * @param[in] the notification function.
 * @return the error statues.
 */
ES_t TIMER_enuSetCallBack(u8 Copy_u8InterruptId, void (*Copy_pvCallBackFunction)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	if(Copy_pvCallBackFunction != NULL)
	{
		switch(Copy_u8InterruptId)
		{
		case TIMER0:
			Global_pvTimerCallBackArr[TIMER0] = Copy_pvCallBackFunction;
			break;
		case TIMER1:
			Global_pvTimerCallBackArr[TIMER1] = Copy_pvCallBackFunction;
			break;
		case TIMER1A:
			Global_pvTimerCallBackArr[TIMER1A] = Copy_pvCallBackFunction;
			break;
		case TIMER1B:
			Global_pvTimerCallBackArr[TIMER1B] = Copy_pvCallBackFunction;
			break;
		case TIMER2:
			Global_pvTimerCallBackArr[TIMER2] = Copy_pvCallBackFunction;
			break;
		case ICU_INT:
			Global_pvTimerCallBackArr[ICU_INT] = Copy_pvCallBackFunction;
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState;
}

/*====================== ISR Functions ======================*/

/*Timer/Counter1 Capture Event*/

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	static u8 local_u8Counter = 0;
	local_u8Counter++;
	if(local_u8Counter == 1)
	{
		Global_u16PeriodTicks1 = ICR1;
	}
	else if(local_u8Counter == 2)
	{
		Global_u16PeriodTicks2 = ICR1;
		Toggle_bit(TCCR1B,TCCR1B_ICES1);
	}
	else if(local_u8Counter == 3)
	{
		Global_u16ONTicks = ICR1;

		Global_u16ONTicks -= (Global_u16PeriodTicks2);
		Clr_bit(TIMSK,TIMSK_TICIE1);
	}
}

/*========================== ISRs of Normal (Overflow) timer interrupts ==========================*/

/*timer/counter 0 overflow mode ISR*/

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(Global_pvTimerCallBackArr[TIMER0] != NULL)
	{
		Global_u32Timer0Cntr++;
		if(Global_u32Timer0Cntr == Global_u32ReqTimer0Cntr)
		{
			Global_u32Timer0Cntr = 0;
			TCNT0 = Global_u32Timer0Preload ;
			Global_pvTimerCallBackArr[TIMER0]();
		}
	}
}

/*timer/counter 1 overflow mode ISR*/

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void){
	if(Global_pvTimerCallBackArr[TIMER1] != NULL)
	{
		Global_u32Timer1Cntr++;
		if(Global_u32Timer1Cntr == Global_u32ReqTimer1Cntr)
		{
			TCNT1 = Global_u32Timer1Preload ;
			Global_u32Timer1Cntr = 0;
			Global_pvTimerCallBackArr[TIMER1]();
		}
	}
}

/*timer/counter 2 overflow mode ISR*/


void __vector_5 (void) __attribute__((signal));
void __vector_5 (void){

	if(Global_pvTimerCallBackArr[TIMER2] != NULL)
	{
		Global_u32Timer2Cntr++;
		if(Global_u32Timer2Cntr == Global_u32ReqTimer2Cntr)
		{
			TCNT2 = Global_u32Timer2Preload ;
			Global_u32Timer2Cntr = 0;
			Global_pvTimerCallBackArr[TIMER2]();
		}
	}
}

/*========================== ISRs of Compare Match timer interrupts ==========================*/

/*timer0 compare match ISR*/

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	if(Global_pvTimerCallBackArr[TIMER0] != NULL)
	{
		if(Global_u8Timer0CTCFlag){
			OCR0 = 0xff;
		}
		Global_u32Timer0Cntr++;
		if(Global_u32Timer0Cntr == Global_u32ReqTimer0Cntr)
		{
			if(Global_u8Timer0CTCFlag)
			{
				OCR0 = Global_f32Timer0CTCVal;
			}
			Global_u32Timer0Cntr = 0;
			Global_pvTimerCallBackArr[TIMER0]();

		}
	}
}

/*timer1 A compare match ISR*/

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void){
	if(Global_pvTimerCallBackArr[TIMER1A] != NULL)
	{
		if(Global_u8Timer1CTCFlag)
		{
			OCR1A = Global_f32Timer1CTCVal;
		}
		Global_u32Timer1Cntr++;
		if(Global_u32Timer1Cntr == Global_u32ReqTimer1Cntr)
		{
			if(Global_u8Timer1CTCFlag)
			{
				OCR1A = 0xffff;
			}
			Global_u32Timer1Cntr = 0;
			Global_pvTimerCallBackArr[TIMER1A]();
		}
	}
}

/*timer1 B compare match ISR*/

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void){
	if(Global_pvTimerCallBackArr[TIMER1B] != NULL)
	{
		if(Global_u8Timer1CTCFlag)
		{
			OCR1B = Global_f32Timer1CTCVal;
		}
		Global_u32Timer1Cntr++;
		if(Global_u32Timer1Cntr == Global_u32ReqTimer1Cntr)
		{
			if(Global_u8Timer1CTCFlag)
			{
				OCR1B = 0xffff;
			}
			Global_u32Timer1Cntr = 0;
			Global_pvTimerCallBackArr[TIMER1B]();
		}
	}
}

/*timer2 compare match ISR*/

void __vector_4 (void) __attribute__((signal));
void __vector_4 (void){
	if(Global_pvTimerCallBackArr[TIMER2] != NULL)
	{
		if(Global_u8Timer2CTCFlag)
		{
			OCR2 = 0xff;
		}
		Global_u32Timer2Cntr++;
		if(Global_u32Timer2Cntr == Global_u32ReqTimer2Cntr)
		{
			if(Global_u8Timer2CTCFlag)
			{
				OCR2 = Global_f32Timer2CTCVal;
			}
			Global_u32Timer2Cntr = 0;
			Global_pvTimerCallBackArr[TIMER2]();
		}
	}

}



/*========================== Static Functions to set the desired time needed in case of normal mode or CTC mode ==========================*/

static void TIMER_VidSetTimer0OVFTime(f32 Copy_f32TimerCtr)
{
	f32 Local_f32FractionCount;
	u32 Local_u32preload;
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer0Cntr = 1;
		Global_u32Timer0Preload = 0;
		TCNT0 = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* integer */
		{
			Global_u32ReqTimer0Cntr = Copy_f32TimerCtr;
			Global_u32Timer0Preload = 0;
			TCNT0 = 0;
		}
		else /* float */
		{
			// preload = 2^n(1-0.y) = 2^n - 0.y*2^n  // 0.y = Copy_f32TimerCtr - (u32)Copy_f32TimerCtr

			Local_f32FractionCount = TIMER0_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);  // 2^n * 0.y

			Local_u32preload = TIMER0_MAX - Local_f32FractionCount;

			Global_u32ReqTimer0Cntr = ((u32)Copy_f32TimerCtr) + 1;

			Global_u32Timer0Preload = Local_u32preload;

			TCNT0 = Local_u32preload;
		}
	}
	else if (Copy_f32TimerCtr < 1) // 0.y = Copy_f32TimerCtr
	{
		Local_f32FractionCount = TIMER0_MAX * Copy_f32TimerCtr;

		Local_u32preload = TIMER0_MAX - Local_f32FractionCount;

		Global_u32ReqTimer0Cntr = 1;

		Global_u32Timer0Preload = Local_u32preload;

		TCNT0 = Local_u32preload;
	}
}

static void TIMER_VidSetTimer1OVFTime(f32 Copy_f32TimerCtr)
{
	f32 Local_f32FractionCount;
	u32 Local_u32preload;
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer1Cntr = 1;
		Global_u32Timer1Preload = 0;
		TCNT1 = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* integer */
		{
			Global_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr;
			Global_u32Timer1Preload = 0;
			TCNT1 = 0;
		}
		else /* float */
		{
			Local_f32FractionCount = TIMER1_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
			Local_u32preload = TIMER1_MAX - Local_f32FractionCount;
			Global_u32ReqTimer1Cntr = ((u32)Copy_f32TimerCtr) + 1;
			Global_u32Timer1Preload = Local_u32preload;
			TCNT1 = Local_u32preload;
		}
	}
	else if (Copy_f32TimerCtr < 1)
	{
		Local_f32FractionCount = TIMER1_MAX * Copy_f32TimerCtr;
		Local_u32preload = TIMER1_MAX - Local_f32FractionCount;
		Global_u32ReqTimer1Cntr = 1;
		Global_u32Timer1Preload = Local_u32preload;
		TCNT1 = Local_u32preload;
	}
}

static void TIMER_VidSetTimer2OVFTime(f32 Copy_f32TimerCtr)
{
	f32 Local_f32FractionCount;
	u32 Local_u8preload;
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer2Cntr = 1;
		Global_u32Timer2Preload = 0;
		TCNT2 = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if ((Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0)) /* integer */
		{
			Global_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr;
			Global_u32Timer2Preload = 0;
			TCNT2 = 0;
		}
		else /* float */
		{
			Local_f32FractionCount = TIMER2_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
			Local_u8preload = TIMER2_MAX - Local_f32FractionCount;
			Global_u32ReqTimer2Cntr = ((u32)Copy_f32TimerCtr) + 1;
			Global_u32Timer2Preload = Local_u8preload;
			TCNT2 = Local_u8preload;
		}
	}
	else if (Copy_f32TimerCtr < 1)
	{
		Local_f32FractionCount = TIMER2_MAX * Copy_f32TimerCtr;
		Local_u8preload = TIMER2_MAX - Local_f32FractionCount;
		Global_u32ReqTimer2Cntr = 1;
		Global_u32Timer2Preload = Local_u8preload;
		TCNT2 = Local_u8preload;
	}
}

static void TIMER_VidSetTIMER0CTCTime(f32 Copy_f32TimerCtr)
{
	//f32 Local_f32FractionCount;
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer0Cntr = 1;
		OCR0 = 0xff;
		Global_u8Timer0CTCFlag = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* integer */
		{
			Global_u32ReqTimer0Cntr = (u32)Copy_f32TimerCtr;
			OCR0 = 0xff;
			Global_u8Timer0CTCFlag = 0;
		}
		else /* float */
		{
			Global_f32Timer0CTCVal = TIMER0_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
			Global_u32ReqTimer0Cntr = (u32)Copy_f32TimerCtr + 1;
			OCR0 = Global_f32Timer0CTCVal;
			Global_u8Timer0CTCFlag = 1;
		}
	}
	else if (Copy_f32TimerCtr < 1)
	{
		Global_u32ReqTimer0Cntr = 1;
		OCR0 = TIMER0_MAX * Copy_f32TimerCtr;
		Global_u8Timer0CTCFlag = 0;
	}
}

static void TIMER_VidSetTIMER1CTCTime(f32 Copy_f32TimerCtr)
{
	//f32 Local_f32FractionCount;
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer1Cntr = 1;
		if (TIMER1_CTC_STATE_A == TIMER_ENABLED)
		{
			OCR1A = 0xffff;
		}
		if (TIMER1_CTC_STATE_B == TIMER_ENABLED)
		{
			OCR1B = 0xffff;
		}
		Global_u8Timer1CTCFlag = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* integer */
		{
			Global_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr;
			if (TIMER1_CTC_STATE_A == TIMER_ENABLED)
			{
				OCR1A = 0xffff;
			}
			if (TIMER1_CTC_STATE_B == TIMER_ENABLED)
			{
				OCR1B = 0xffff;
			}
			Global_u8Timer1CTCFlag = 0;
		}
		else /* float */
		{
			Global_f32Timer1CTCVal = (f32)TIMER1_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
			Global_u32ReqTimer1Cntr = (u32)Copy_f32TimerCtr + 1;

			if (TIMER1_CTC_STATE_A == TIMER_ENABLED)
			{
				OCR1A = Global_f32Timer1CTCVal;
			}
			if (TIMER1_CTC_STATE_B == TIMER_ENABLED)
			{
				OCR1B = Global_f32Timer1CTCVal;
			}
			Global_u8Timer1CTCFlag = 1;
		}
	}
	else if (Copy_f32TimerCtr < 1)
	{
		//Local_f32FractionCount = TIMER1_MAX * Copy_f32TimerCtr;
		Global_u32ReqTimer1Cntr = 1;
		if (TIMER1_CTC_STATE_A == TIMER_ENABLED)
		{
			OCR1A =	(TIMER1_MAX * Copy_f32TimerCtr);
		}
		if (TIMER1_CTC_STATE_B == TIMER_ENABLED)
		{
			OCR1B = (TIMER1_MAX * Copy_f32TimerCtr);
		}
	}
	Global_u8Timer1CTCFlag = 0;
}

static void TIMER_VidSetTIMER2CTCTime(f32 Copy_f32TimerCtr)
{
	if (Copy_f32TimerCtr == 1)
	{
		Global_u32ReqTimer2Cntr = 1;
		OCR2 = 0xff;
		Global_u8Timer2CTCFlag = 0;
	}
	else if (Copy_f32TimerCtr > 1)
	{
		if (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr == 0) /* integer */
		{
			Global_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr;
			OCR2 = 0xff;
			Global_u8Timer2CTCFlag = 0;
		}
		else /* float */
		{
			Global_f32Timer2CTCVal = TIMER2_MAX * (Copy_f32TimerCtr - (u32)Copy_f32TimerCtr);
			Global_u32ReqTimer2Cntr = (u32)Copy_f32TimerCtr + 1;
			OCR2 = Global_f32Timer2CTCVal;
			Global_u8Timer2CTCFlag = 1 ;
		}
	}
	else if (Copy_f32TimerCtr < 1)
	{
		Global_u32ReqTimer2Cntr = 1;
		OCR2 = TIMER2_MAX * Copy_f32TimerCtr;
		Global_u8Timer2CTCFlag = 0;
	}
}


