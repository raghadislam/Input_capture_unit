/*
 * Seven_segment_config.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef SEVEN_SEGMENT_CONFIG_H_
#define SEVEN_SEGMENT_CONFIG_H_

#define NUM_OF_SEG	 2



typedef struct {

	u8 SEG_u8APort;
	u8 SEG_u8APin;

	u8 SEG_u8BPort;
	u8 SEG_u8BPin;

	u8 SEG_u8CPort;
	u8 SEG_u8CPin;

	u8 SEG_u8DPort;
	u8 SEG_u8DPin;

	u8 SEG_u8EPort;
	u8 SEG_u8EPin;

	u8 SEG_u8FPort;
	u8 SEG_u8FPin;

	u8 SEG_u8GPort;
	u8 SEG_u8GPin;

	u8 SEG_u8CMNPort;
	u8 SEG_u8CMNPin;

	u8 SEG_u8DOTPort;
	u8 SEG_u8DOTPin;

	u8 SEG_TYPE;

}SEG_t;

#endif /* SEVEN_SEGMENT_CONFIG_H_ */
