/*
 * WDT_interface.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_WDT_WDT_INT_H_
#define ATMEGA32_CTOS_MCAL_WDT_WDT_INT_H_

/* Macros for WatchDog Timer Periods at 5V */
#define WDT_16MS	0
#define WDT_32MS	1
#define WDT_65MS	2
#define WDT_130MS	3
#define WDT_260MS	4
#define WDT_520MS	5
#define WDT_1000MS	6
#define WDT_2100MS	7

/**
 * @brief Function to set the time out period for the Watch Dog timer
 *
 * @param  Copy_u16Time: 1- WDT_16MS
 *                       2- WDT_32MS
 *                       3- WDT_65MS
 *                       4- WDT_130MS
 *                       5- WDT_260MS
 *                       6- WDT_520Ms
 *                       7- WDT_1000MS
 *                       8- WDT_2100MS
 * @return error stet
 */
ES_t WDT_enuSetTimeOut(u16 Copy_u16Time);


/**
 * @brief Function to enable the Watch Dog Timer
 * @param  void
 * @return void
 */
void WDT_vidEnable(void);


/**
 * @brief Function to disable the Watch Dog Timer
 * @param  void
 * @return void
 */
void WDT_vidDisable(void);


#endif /* ATMEGA32_CTOS_MCAL_WDT_WDT_INT_H_ */
