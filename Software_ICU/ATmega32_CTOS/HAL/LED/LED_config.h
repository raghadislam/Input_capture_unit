/*
 * LED_config.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#define NUM_OF_LED	3

typedef struct
{
	u8 LED_u8PortID;

	u8 LED_u8PinID;

	u8 LED_u8connection; // sink or source

	u8 LED_u8InitState;

}LED_t;


#endif /* LED_CONFIG_H_ */
