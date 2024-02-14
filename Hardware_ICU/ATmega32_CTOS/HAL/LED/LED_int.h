/*
 * LED_int.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef LED_INT_H_
#define LED_INT_H_


ES_t LED_enuInit(LED_t* Copy_pstrLedConfig);

ES_t LED_enuLedTurnON(LED_t* Copy_pstrLedID);

ES_t LED_enuLedTurnOFF(LED_t* Copy_pstrLedID);




#endif /* LED_INT_H_ */
