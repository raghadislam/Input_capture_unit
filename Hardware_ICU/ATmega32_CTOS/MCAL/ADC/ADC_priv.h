/*
 * ADC_priv.h
 *
 *  Created on: Sep 21, 2023
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_ADC_ADC_PRIV_H_
#define ATMEGA32_CTOS_MCAL_ADC_ADC_PRIV_H_

/*======================= private macros ======================= */

/* ADC reference voltage selection*/

#define ADC_AREF		    88
#define ADC_VCC		        99
#define ADC_INTERNAL_VREF	11

/*define the ADC right or left adjustment*/

#define ADC_RIGHT_ADJUST    77
#define ADC_LEFT_ADJUST	  	66

/* define the Enable/Disable state of the ADC peripheral, ADC interrupt and auto trigger */

#define ADC_ENABLED			55
#define ADC_DISABLED	    34

#define ADC_INT_ENABLED		67
#define ADC_INT_DISABLED    44

#define ADC_AUTO_TRIGGER_ENABLED		58
#define ADC_AUTO_TRIGGER_DISABLED	    47

/*ADC prescaler selection*/

#define ADC_PRESCALER_2     0x0
#define ADC_PRESCALER_4     0x2
#define ADC_PRESCALER_8     0x3
#define ADC_PRESCALER_16    0x4
#define ADC_PRESCALER_32    0x5
#define ADC_PRESCALER_64    0x6
#define ADC_PRESCALER_128   0x7

/*ADC resolution selection*/

#define ADC_8BIT			5
#define ADC_10BIT			7


/*======================= ADC multiplexer selection register =======================*/

#define ADMUX 		        *((volatile u8*)0x27)

/* reference selection bit 0 */
#define ADMUX_REFS1 		7
/* reference selection bit 1 */
#define ADMUX_REFS0 		6
/* ADC left adjust result */
#define ADMUX_ADLAR 		5

/* Analog Channel and Gain Selection Bits */
#define ADMUX_MUX4 			4
#define ADMUX_MUX3 			3
#define ADMUX_MUX2 			2
#define ADMUX_MUX1 			1
#define ADMUX_MUX0 			0


/*======================== ADC control and statues register A ========================*/

#define ADCSRA 	        	*((volatile u8*)0x26)


/*ADC enable bit*/
#define ADCSRA_ADEN 		7
/*ADC start conversion*/
#define ADCSRA_ADSC 		6
/*ADC auto trigger enable*/
#define ADCSRA_ADATE	    5
/*ADC interrupt flag*/
#define ADCSRA_ADIF	        4
/*ADC interrupt enable*/
#define ADCSRA_ADIE	        3

/*ADC prescaler bits*/
#define ADCSRA_ADPS2        2
#define ADCSRA_ADPS1        1
#define ADCSRA_ADPS0        0

/*======================= special function I/O register =======================*/

#define SFIOR 		        *((volatile u8*)0x50)

/*ADC Auto Trigger Source bits*/
#define SFIOR_ADTS2			7
#define SFIOR_ADTS1			6
#define SFIOR_ADTS0			5


/*ADC Auto Trigger Source bits*/
#define ADC_FREE_RUNNING			0
#define ADC_ANALOG_COMPARATOR		1
#define ADC_EXTI0					2
#define ADC_TIMER0_COMPARE_MATCH	3
#define ADC_TIMER0_OVERFLOW			4
#define ADC_TIMER1_COMPARE_MATCH_B  5
#define ADC_TIMER1_OVERFLOW			6
#define ADC_TIMER1_CAPTURE_EVENT	7

/* single conversion mode*/
#define ADC_SINGLE_CONVERSION       71


/*======================= ADCL and ADCH =======================*/

#define ADCH 		        *((volatile u16*)0x25)

#define ADCL 		        *((volatile u16*)0x24)

#define ADCVAL_10BITS       *((volatile u16 *)(0x24))



/*===================== assert parameters =====================*/


#define IS_VALID_PRESCALER(PRESCALER) (((PRESCALER) == ADC_PRESCALER_2 ) || \
                                      ((PRESCALER)  == ADC_PRESCALER_4 ) || \
								      ((PRESCALER)  == ADC_PRESCALER_8 ) || \
								      ((PRESCALER)  == ADC_PRESCALER_16) || \
								      ((PRESCALER)  == ADC_PRESCALER_32) || \
								      ((PRESCALER)  == ADC_PRESCALER_64) || \
                                      ((PRESCALER)  == ADC_PRESCALER_128 ))
#define PRESCALER_MASK 	 0b11111000







#define IS_VALID_AUTO_TRIGGER_SOURCE(SOURCE) (((SOURCE) == ADC_FREE_RUNNING          )|| \
											 ((SOURCE)  == ADC_ANALOG_COMPARATOR     )|| \
											 ((SOURCE)  == ADC_EXTI0                 )|| \
											 ((SOURCE)  == ADC_TIMER0_COMPARE_MATCH  )|| \
											 ((SOURCE)  == ADC_TIMER0_OVERFLOW       )|| \
											 ((SOURCE)  == ADC_TIMER1_COMPARE_MATCH_B)|| \
											 ((SOURCE)  == ADC_TIMER1_OVERFLOW       )|| \
											 ((SOURCE)  == ADC_TIMER1_CAPTURE_EVENT  ))

#define AUTO_TRIGGER_SOURCE_MASK 	 0b00011111


#define IS_VALID_CHANNEL(CHANNEL) ((CHANNEL) >=0 && (CHANNEL)<= 31)

#define CHANNEL_SELECTION_MASK   	 0b11100000
#define CLEAR_REGISTER_MASK 		 0b00000000


#define LOW 			0
#define HIGH			1

#define IDLE 9
#define BUSY 8





#endif /* ATMEGA32_CTOS_MCAL_ADC_ADC_PRIV_H_ */
