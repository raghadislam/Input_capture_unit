/*
 * timer_int.h
 *
 *  Created on: Dec 18, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_TIMER_TIMER_INT_H_
#define ATMEGA32_CTOS_MCAL_TIMER_TIMER_INT_H_

/*================= timers ID =================*/

#define TIMER0				0
#define TIMER1				1
#define TIMER1A				2
#define TIMER1B				3
#define TIMER2				4


/*============== ICU interrupt ID ==============*/

#define ICU_INT				5


/*======= ICU interrupt trigger options ========*/

#define ICU_RISING_EDGE		21
#define ICU_FALLING_EDGE	22


/**
 * @brief functions to initialize timer prepherals (0, 1, 2).
 *
 * @return the error statues.
 */
ES_t TIMER0_enuInit(void);
ES_t TIMER1_enuInit(void);
ES_t TIMER2_enuInit(void);


/**
 * @brief function to disable a specific timer prepheral.
 *
 * @param[in] TIMER id:  	  1- TIMER0
 *                            2- TIMER1
 *                            3- TIMER2
 *
 * @return the error statues.
 */
ES_t TIMER_enuDisable(u8 Copy_u8TimerId);

/**
 * @brief function to set the Compare Match value of a specific timer prepheral for post build.
 *
 * @param[in] Copu_u16Val:  	1- TIMER0
 *                            	2- TIMER1A
 *                            	3- TIMER1B
 *                            	4- TIMER2
 *
 * @param[in] Compare Match Value.
 *
 * @return the error statues.
 */
ES_t TIMER_enuSetCompareMatchVAl(u8 Copy_u8TimerID, u16 Copy_u16Val);


/**
 * @brief function to get the value of a specific timer prepheral for post build.
 *
 * @param[in] Copu_u16Val:  	 1- TIMER0
 *                           	 2- TIMER1A
 *                            	 3- TIMER1B
 *                           	 4- TIMER2
 *
 * @param[out] Copu_u16Val : Timer reading.
 *
 * @return the error statues.
 */
ES_t Timer_enuGetTimerVal(u8 Copy_TimerId, u16* Copu_u16Val);


/**
 * @brief function to set the preload value of a specific timer prepheral for post build.
 *
 * @param[in] Copy_u8TimerId:  	1- TIMER0
 *                           	2- TIMER1A
 *                            	3- TIMER1B
 *                            	4- TIMER2
 *
 * @param[in]  Copu_u16Val:  setting Value.
 *
 * @return the error statues.
 */
ES_t Timer_enuSetTimerVal(u8 Copy_TimerId, u16 Copu_u16Val);


/**
 * @brief function to set the desired time for the chosen timer prepheral.
 *
 * @param[in] Copy_u8TimerId:	1- TIMER0
 *                           	2- TIMER1A
 *                           	3- TIMER1B
 *                           	4- TIMER2
 *
 *@param[in] Copy_u32Time_us: required time in microseconed.
 *
 * @return the error statues.
 */
ES_t TIMER_enuSetDesiredTime_us(u8 Copy_u8TimerId, f32 Copy_u32Time_us);


/**
 * @brief function to set the desired Duty cycle of the PWM signal for the chosen timer prepheral.
 *
 * @param[in] TIMER id:  	  1- TIMER0
 *                            2- TIMER1A
 *                            3- TIMER1B
 *                            4- TIMER2
 *
 *@param[in] Copy_u8DutyCycle: Duty Cycle value between 0 to 100.
 *
 * @return the error statues.
 */
ES_t TIMER_enuSetDutyCycle(u8 Copy_u8TimerID, u8 Copy_u8DutyCycle);


/**
 * @brief function to cahnge the Trigger Edge for the ICU in timer 1.
 *
 * @param[in] trigger edge:   1- ICU_RISING_EDGE
 *                            2- ICU_FALLING_EDGE
 *
 * @return the error statues.
 */
ES_t ICU_enuSetTriggerEdge(u8 Copy_u8TRiggerEdge);


/**
 * @brief void function to Disable ICU Interrupt.
 */
void ICU_vidDisableInterrupt();


/**
 * @brief void function to Enable ICU Interrupt.
 */
void ICU_vidEnableInterrupt();


/**
 * @brief function to Get the on time for a signal using ICU.
 *
 * @param[out] Copy_u16OnTime: the on time of the signal
 *
 * @return the error statues.
 */
ES_t ICU_enuGetOnTime_us(u16* Copy_u16OnTime);


/**
 * @brief function to Get the period time for a signal using ICU.
 *
 * @param[out] Copy_u16Period: the period of the signal
 *
 * @return the error statues.
 */
ES_t ICU_enuGetPeriod_us(u16* Copy_u16Period);


/**
 * @brief function to Get the Duty Cycle for a signal using ICU.
 *
 * @param[out] Copy_u8DutyCycle: the Duty Cycle of the signal
 *
 * @return the error statues.
 */
ES_t ICU_enuGetDutyCycle(u8* Copy_u8DutyCycle);


/**
 * @brief function to get the value of a the input capture register (ICR1).
 *
 * @param[out] input capture register reading.
 *
 * @return the error statues.
 */
ES_t ICU_enuGetInputCapture(u16* Copy_pu16InputCapture);


/**
 * @brief function to receive the addresse of the ISR function of a specific timer prepheral.
 *
 * @param[in] TIMER id:  	  1- TIMER0
 * 							  2- TIMER1  (overflow)
 *                            2- TIMER1A (CTC A)
 *                            3- TIMER1B (CTC B)
 *                            4- TIMER2
 *
 * @param[in] the notification function.
 *
 * @return the error statues.
 */
ES_t TIMER_enuSetCallBack(u8 Copy_TimerId, void (*Copy_pvCallBackFunction)(void));


#endif /* ATMEGA32_CTOS_MCAL_TIMER_TIMER_INT_H_ */
