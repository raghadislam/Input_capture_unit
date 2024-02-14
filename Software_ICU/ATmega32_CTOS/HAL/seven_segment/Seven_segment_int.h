/*
 * Seven_segment_int.h
 *
 *  Created on: Jul 16, 2023
 *      Author: DeLL
 */

#ifndef SEVEN_SEGMENT_INT_H_
#define SEVEN_SEGMENT_INT_H_

ES_t Seven_segment_enuInit(SEG_t* Copy_AstrSegConfig);

ES_t Seven_segment_enuDisplayNum( u8 Copy_u8SegID , u8 Copy_u8Num);

ES_t Seven_segment_enuEnableCommon(u8 Copy_u8SegID);

ES_t Seven_segment_enuDisableCommon(u8 Copy_u8SegID);

ES_t Seven_segment_enuEnableDot(u8 Copy_u8SegID);

ES_t Seven_segment_enuDisableDot(u8 Copy_u8SegID);

ES_t Seven_segment_enuClearDisplay(u8 Copy_u8SegID);




#endif /* SEVEN_SEGMENT_INT_H_ */
