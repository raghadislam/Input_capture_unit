/*
 * EXTI_config.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_


typedef struct {
	u8 EXTI_u8State;
	u8 EXTI_u8Sense;
}EXTI_t;


/* Determine the sense control for each pin
 *
 * options: 1- FALLING_EDGE
 * 			2- RISING_EDGE
 * 			3- ON_CHANGE
 * 			4- LOW_LEVEL                 */

#define EXTI_INT0_SENSE		FALLING_EDGE
#define EXTI_INT1_SENSE		FALLING_EDGE
#define EXTI_INT2_SENSE		FALLING_EDGE

/* Determine the initial state for each pin
 *
 * options: 1- ENABLE
 * 			2- DISABLE
 * 			                             */
#define EXTI_INT0_STATE  ENABLED
#define EXTI_INT1_STATE  ENABLED
#define EXTI_INT2_STATE  DISABLED





#endif /* EXTI_CONFIG_H_ */
