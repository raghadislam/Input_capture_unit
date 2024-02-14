/*
 * WDT_priv.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Raghad Islam
 */

#ifndef ATMEGA32_CTOS_MCAL_WDT_WDT_PRIV_H_
#define ATMEGA32_CTOS_MCAL_WDT_WDT_PRIV_H_

/**************************************************************************************
 *                                  Watch Dog Registers                               *
 **************************************************************************************/

#define WDTCR			*((volatile u8*)0x41)			/* Watchdog Timer Control Register */
#define WDTCR_WDTOE		4								/* Watchdog Turn-off Enable bit */
#define WDTCR_WDE		3								/* Watchdog Enable */
#define WDTCR_WDP2		2								/* Watchdog Timer Prescaler 2 */
#define WDTCR_WDP1		1								/* Watchdog Timer Prescaler 1 */
#define WDTCR_WDP0		0								/* Watchdog Timer Prescaler 0 */


/* Time selections at VCC = 5.0V */

#define	WDT_16MS		0							/* 17.1ms at VCC = 3.0V */
#define	WDT_32MS		1   				        /* 34.3ms at VCC = 3.0V */
#define	WDT_65MS		2       				    /* 68.5ms at VCC = 3.0V */
#define	WDT_130MS		3       				    /* 0.14 s at VCC = 3.0V */
#define	WDT_260MS		4       				    /* 0.27 s at VCC = 3.0V */
#define	WDT_520Ms		5       				    /* 0.55 s at VCC = 3.0V */
#define	WDT_1000MS		6       				    /* 1.1  s at VCC = 3.0V */
#define	WDT_2100MS		7           				/* 2.2  s at VCC = 3.0V */
#define WDT_MASK		0b11111000

/* Private Macros for Watch Dog Timer state */
#define WDT_ENABLE 		1
#define WDT_DISABLE 	0

#endif /* ATMEGA32_CTOS_MCAL_WDT_WDT_PRIV_H_ */
