/*
 * EXTI_int.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Raghad Islam
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_

#define EXTI_INT0 		 33
#define EXTI_INT1 		 34
#define EXTI_INT2 		 35


#define FALLING_EDGE	 66
#define RISING_EDGE 	 36
#define ON_CHANGE		 56
#define LOW_LEVEL 		 86

/* initialization function */

ES_t EXTI_enuInit(EXTI_t * Copy_pstrEXTIConfig);

/**
 * @brief function to set the required sense control of a specific pin for post build.
 *
 *
 * @param[in] EXTI pin:       1- EXTI_INT0
 *                            2- EXTI_INT1
 *                            3- EXTI_INT2
 *
 * @param[in] Sense Control:  1- FALLING_EDGE
 *                            2- RISING_EDGE
 *                            3- ON_CHANGE
 *                            4- LOW_LEVEL
 * @return the error statues
 */

ES_t EXTI_enuSetSenseCtrl(u8 Copy_u8INTPin, u8 Copy_u8Sense);


/**
 * @brief function to enable the peripheral control of a specific pin for post build.
 *
 * @param[in] EXTI pin:       1- EXTI_INT0
 *                            2- EXTI_INT1
 *                            3- EXTI_INT2
 * @return the error statues
 */
ES_t EXTI_enuIntEnable(u8 Copy_u8INTPin);

/**
 * @brief function to disable the peripheral control of a specific pin for post build.
 *
 * @param[in] EXTI pin:       1- EXTI_INT0
 *                            2- EXTI_INT1
 *                            3- EXTI_INT2
 * @return the error statues
 */
ES_t EXTI_enuIntDisable(u8 Copy_u8INTPin);


/*functions to receive the addresses of the ISR for INT0, INT1 and INT2.*/

ES_t EXIT_enuINT0SetCallBack(void(*Copy_pvUserISR)(void));

ES_t EXIT_enuINT1SetCallBack(void(*Copy_pvUserISR)(void));

ES_t EXIT_enuINT2SetCallBack(void(*Copy_pvUserISR)(void));



#endif /* EXTI_INT_H_ */
