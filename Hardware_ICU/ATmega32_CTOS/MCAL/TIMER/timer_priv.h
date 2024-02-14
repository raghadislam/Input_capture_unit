/*
 * timer_priv.h
 *
 *  Created on: Dec 18, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_TIMER_TIMER_PRIV_H_
#define ATMEGA32_CTOS_MCAL_TIMER_TIMER_PRIV_H_


/**************************************************************************************
 *                                  Timer0 Registers                                  *
 **************************************************************************************/

#define TCCR0 			*((volatile u8*)0x53)		/* Timer0 control register */
#define TCCR0_CS00		0							/* Prescaler bit 0 */
#define TCCR0_CS01		1							/* Prescaler bit 1 */
#define TCCR0_CS02		2							/* Prescaler bit 2 */
#define TCCR0_WGM01		3							/* Waveform generation mode 1 */
#define TCCR0_COM00		4							/* Compare Output Mode, Phase Correct, fast and non-PWM Mod0 */
#define TCCR0_COM01		5							/* Compare Output Mode, Phase Correct, fast and non-PWM Mod1 */
#define TCCR0_WGM00		6							/* Waveform generation mode 0 */
#define TCCR0_FOC0		7							/*Force Output Compare, must be set to 0 at PWM mode*/

#define TCNT0			*((volatile u8*)0x52)		/*Timer/Counter0 (8 Bits)*/


#define OCR0			*((volatile u8*)0x5c)		/* Output compare register */


#define TIMSK			*((volatile u8*)0x59)		/* Timer mask */
#define TIMSK_OCIE0		1							/* Timer/Counter0 Output Compare Match Interrupt Enable */
#define TIMSK_TOIE0		0							/*Timer/Counter0 Overflow Interrupt Enable*/

/**************************************************************************************
 *                                  Timer1 Registers                                  *
 **************************************************************************************/

#define TCCR1A			*((volatile u8*)0x4f)		/*Timer/Counter1 Control Register A*/
#define TCCR1A_WGM10	0							/*Waveform Generation Mode*/
#define TCCR1A_WGM11	1							/*Waveform Generation Mode*/
#define TCCR1A_FOC1B	2							/*Force Output Compare for Compare unit B*/
#define TCCR1A_FOC1A	3							/*Force Output Compare for Compare unit A*/
#define TCCR1A_COM1B0	4							/*Compare Output Mode for Compare unit B */
#define TCCR1A_COM1B1	5							/*Compare Output Mode for Compare unit B */
#define TCCR1A_COM1A0	6							/*Compare Output Mode for Compare unit A */
#define TCCR1A_COM1A1	7							/*Compare Output Mode for Compare unit A */


#define TCCR1B			*((volatile u8*)0x4e)		/*Timer/Counter1 Control Register B*/
#define TCCR1B_CS10		0                           /* Prescaler bit 0 */
#define TCCR1B_CS11		1                           /* Prescaler bit 1 */
#define TCCR1B_CS12		2                           /* Prescaler bit 2 */
#define TCCR1B_WGM12	3                           /* Waveform generation mode  */
#define TCCR1B_WGM13	4                           /* Waveform generation mode  */
#define TCCR1B_ICES1	6							/*  Input Capture Edge Select */
#define TCCR1B_ICNC1	7							/*  Input Capture Noise Canceler */


#define TIMSK_TOIE1		2							/* Timer/Counter1, Input Capture Interrupt Enable */
#define TIMSK_OCIE1B	3                           /* Timer/Counter1, Timer/Counter1, Output Compare B Match Interrupt Enable */
#define TIMSK_OCIE1A	4                           /* Timer/Counter1, Timer/Counter1, Output Compare A Match Interrupt Enable*/
#define TIMSK_TICIE1	5                           /* Timer/Counter1, Overflow Interrupt Enable */


#define TCNT1			*((volatile u16*)0x4c)

#define OCR1A			*((volatile u16*)0x4a)

#define OCR1B			*((volatile u16*)0x48)

#define ICR1			*((volatile u16*)0x46) 			/*input capture register*/


/**************************************************************************************
 *                                  Timer2 Registers                                  *
 **************************************************************************************/

#define TCCR2			*((volatile u8*)0x45)			/*Timer/Counter2 Control Register A*/
#define TCCR2_CS20		0                               /* Prescaler bit 0 */
#define TCCR2_CS21		1                               /* Prescaler bit 1 */
#define TCCR2_CS22		2                               /* Prescaler bit 2 */
#define TCCR2_WGM21		3                               /* Waveform generation mode 1 */
#define TCCR2_COM20		4                               /* Compare Output Mode, Phase Correct, fast and non-PWM Mod0 */
#define TCCR2_COM21		5                               /* Compare Output Mode, Phase Correct, fast and non-PWM Mod1 */
#define TCCR2_WGM20		6                               /* Waveform generation mode 0 */
#define TCCR2_FOC2		7                               /*Force Output Compare, must be set to 0 at PWM mode*/

#define TCNT2			*((volatile u8*)0x44)			/*Timer/Counter2 Control Register*/


#define OCR2			*((volatile u8*)0x43)  			/* Output compare register */


#define TIMSK_OCIE2		7								/* Timer/Counter2 Output Compare Match Interrupt Enable */
#define TIMSK_TOIE2		6								/*Timer/Counter2 Overflow Interrupt Enable*/

/** timers mode **/

#define TIMER_MODE_CTC				1
#define TIMER_MODE_OVE 				2
#define TIMER_MODE_PWM 				3
#define TIMER_MODE_PWM_8BIT			4
#define TIMER_MODE_PWM_9BIT			5
#define TIMER_MODE_PWM_10BIT		6
#define TIMER_MODE_FASTPWM			7
#define TIMER_MODE_FAST_PWM_8BIT	8
#define TIMER_MODE_FAST_PWM_9BIT	8
#define TIMER_MODE_FAST_PWM_10BIT	10
#define TIMER_MODE_FASTPWM_ICR1		11
#define TIMER_MODE_FASTPWM_OCRA1	12

/** timers Prescaler **/

#define TIMER_CLK_STOP	 		    2
#define TIMER_NO_PRESCALER 		    1
#define TIMER_PRESCALER_8 		    8
#define TIMER_PRESCALER_64 		    64
#define TIMER_PRESCALER_128			128
#define TIMER_PRESCALER_256		    256
#define TIMER_PRESCALER_1024	    1024
#define TIMER_EXT_PRESCALER_RISING	10
#define TIMER_EXT_PRESCALER_FALLING	11

/** compare match action **/

#define CLEAR_OC		1
#define SET_OC			2
#define TOGGLE_OC		3
#define DISCONNECT_OC	4



/** pwm/fast pwm mode selections **/

#define CLEAR_ON_COMP_SET_ON_TOP	10  /* non inverted */
#define SET_ON_COMP_CLEAR_ON_TOP	11  /* inverted */
#define CLEAR_ON_UP_SET_ON_DOWN		13  /* non inverted */
#define SET_ON_UP_CLEAR_ON_DOWN		14  /* inverted */
#define OC_DISCONNECTED				15


/* Private Macros for Timers initialization */

#define TIMER0			0
#define TIMER1			1
#define TIMER1A			2
#define TIMER1B			3
#define TIMER2			4
#define ICU_INT			5

#define TIMER0_MAX		256ULL
#define TIMER1_MAX		65536ULL
#define TIMER2_MAX		256

#define TIMER_ENABLED	55
#define TIMER_DISABLED	76

#define RISING_EDGE		21
#define FALLING_EDGE	22



/*============== Setting the Timer overflow according to the configured prescaler ==============*/

#define TIMER0_TOVF ((TIMER0_MAX * TIMER0_PRESCALER * 1000000ULL)/ SYSTEM_CLK)
#define TIMER1_TOVF ((TIMER1_MAX * TIMER1_PRESCALER * 1000000ULL)/ SYSTEM_CLK)
#define TIMER2_TOVF ((TIMER2_MAX * TIMER2_PRESCALER * 1000000ULL)/ SYSTEM_CLK)




#endif /* ATMEGA32_CTOS_MCAL_TIMER_TIMER_PRIV_H_ */
