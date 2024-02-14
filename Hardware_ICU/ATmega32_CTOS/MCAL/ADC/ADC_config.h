/*
 * ADC_config.h
 *
 *  Created on: Sep 21, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_ADC_ADC_CONFIG_H_
#define ATMEGA32_CTOS_MCAL_ADC_ADC_CONFIG_H_

/*Determine the initial state of the ADC
 *
 * options: 1- ADC_ENABLED
 * 			2- ADC_DISABLED
 */
#define ADC_INITIAL_STATE   		   ADC_ENABLED


/* Determine the reference voltage
 *
 * options: 1- ADC_AREF
 * 			2- ADC_VCC
 * 			3- ADC_INTERNAL_VREF
 */

#define ADC_REFERENCE_VOLTAGE			ADC_AREF


/* Determine the adjust result
 * options: 1- ADC_RIGHT_ADJUST
 * 			2- ADC_LEFT_ADJUST
 */

#define ADC_ADJUST_RESULT				ADC_LEFT_ADJUST

/*Determine the initial state of the auto trigger
 *
 * options: 1- ADC_AUTO_TRIGGER_ENABLED
 * 			2- ADC_AUTO_TRIGGER_DISABLED
 */

#define ADC_AUTO_TRIGGER_STATE 		    ADC_AUTO_TRIGGER_DISABLED

/*Determine the initial state of the ADC interrupt
 *
 * options: 1- ADC_INT_ENABLED
 * 			2- ADC_INT_DISABLED
 */

#define ADC_INTERRUPT_STATE 		    ADC_INT_DISABLED

/*Determine the ADC Prescaler
 *
 * options: 1- ADC_PRESCALER_2
 * 			2- ADC_PRESCALER_4
 * 			3- ADC_PRESCALER_8
 * 			4- ADC_PRESCALER_16
 * 			5- ADC_PRESCALER_32
 * 			6- ADC_PRESCALER_64
 * 			7- ADC_PRESCALER_128
 */

#define ADC_PRESCALER 				   ADC_PRESCALER_128

/*specify the ADC resolution
 *
 * options: 1- ADC_8BIT
 * 			2- ADC_10BIT
 */

#define ADC_RESOLUTION 			       ADC_8BIT

/*specify the ADC auto trigger source
 *
 * options: 1- ADC_FREE_RUNNING
 *			2- ADC_ANALOG_COMPARATOR
 *			3- ADC_EXTI0
 *			4- ADC_TIMER0_COMPARE_MATCH
 *			5- ADC_TIMER0_OVERFLOW
 *			6- ADC_TIMER1_COMPARE_MATCH_B
 *			7- ADC_TIMER1_OVERFLOW
 *			8- ADC_TIMER1_CAPTURE_EVENT
 */

#define ADC_AUTO_TRIGGER_SOURCE 	ADC_FREE_RUNNING


/*specify the ADC auto trigger conversion mode
 *
 * options: 1- ADC_FREE_RUNNING
 *			2- ADC_SINGLE_CONVERSION
 */
#define ADC_CONVERSION_MODE 	ADC_FREE_RUNNING

/*specify the ADC time out */
#define ADC_u32TIMOUT			1000000000000000

#endif /* ATMEGA32_CTOS_MCAL_ADC_ADC_CONFIG_H_ */
