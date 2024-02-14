/*
 * WDT_config.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_WDT_WDT_CONFIG_H_
#define ATMEGA32_CTOS_MCAL_WDT_WDT_CONFIG_H_


/** Macros for Watch Dog Timer initialization state
 * options: WDT_ENABLE
 *        	WDT_DISABLE
 */
#define WDT_INIT_STATE WDT_DISABLE

/** Macros for WatchDog Timer Periods (Values at typical 5V)
 * options:	 WDT_16MS
 *			 WDT_32MS
 *  	     WDT_65MS
 *  	     WDT_130MS
 *  	     WDT_260MS
 *  	     WDT_520MS
 *  	     WDT_1000MS
 *  	     WDT_2100MS
 */
#define WDT_INIT_PERIOD WDT_16MS


#endif /* ATMEGA32_CTOS_MCAL_WDT_WDT_CONFIG_H_ */
