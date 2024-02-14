/*
 * DIO_int.h
 *
 *  Created on: Jul 15, 2023
 *      Author: Raghad Islam
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

/*=============== DIO ports ID ===============*/

#define DIO_u8PORTA   0
#define DIO_u8PORTB   1
#define DIO_u8PORTC   2
#define DIO_u8PORTD   3

/*=============== DIO pins ID ===============*/

#define DIO_u8PIN0   0
#define DIO_u8PIN1   1
#define DIO_u8PIN2   2
#define DIO_u8PIN3   3
#define DIO_u8PIN4   4
#define DIO_u8PIN5   5
#define DIO_u8PIN6   6
#define DIO_u8PIN7   7

/*============================== DIO functions ==============================*/

/*@brief initializaion function to set the initial direction of all DIO pins.
 *
 * @return error statues
 */
ES_t DIO_enuInit(void);


/*@brief function to set the chosen direction of the entire DIO port.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[in]   Copy_u8Val:	desired direction for all pins of the desired port.
 *
 * @return error statues
 */
ES_t DIO_enuSetPortDir (u8 Copy_u8PortID , u8 Copy_u8Val );


/*@brief function to set the value of the entire DIO port.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[in]   Copy_u8Val:	desired value for all pins of the desired port.
 *
 * @return error statues
 */
ES_t DIO_enuSetPortVal( u8 Copy_u8PortID , u8 Copy_u8Val );


/*@brief function to toggle the value of the entire DIO port.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @return error statues
 */
ES_t DIO_enuTogglePort( u8 Copy_u8PortID );


/*@brief function to read the value of the entire DIO port.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[out]   Copy_pu8Val:	the desired port reading.
 *
 * @return error statue
 */
ES_t DIO_enuGetPortVal( u8 Copy_u8PortID , u8* Copy_pu8Val );


/*@brief function to set the chosen direction of the DIO pin.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[in]	Copy_u8PinID: 	1- DIO_u8PIN0
 *				              	2- DIO_u8PIN1
 *				              	3- DIO_u8PIN2
 *				              	4- DIO_u8PIN3
 *				              	5- DIO_u8PIN4
 *				              	6- DIO_u8PIN5
 *				              	7- DIO_u8PIN6
 *				              	8- DIO_u8PIN7
 *
 * @param[in]   Copy_u8Val:		1- DIO_u8OUTPUT
 * 								2- DIO_u8INPUT
 *
 * @return error statues
 */
ES_t DIO_enuSetPinDir( u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8Val );


/*@brief function to set the chosen value of the DIO pin.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[in]	Copy_u8PinID: 	1- DIO_u8PIN0
 *				              	2- DIO_u8PIN1
 *				              	3- DIO_u8PIN2
 *				              	4- DIO_u8PIN3
 *				              	5- DIO_u8PIN4
 *				              	6- DIO_u8PIN5
 *				              	7- DIO_u8PIN6
 *				              	8- DIO_u8PIN7
 *
 * @param[in]   Copy_u8Val:		1- DIO_u8HIGH
 * 								2- DIO_u8LOW
 *
 * @return error statues
 */
ES_t DIO_enuSetPinVal( u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8Val );


/*@brief function to toggle the value of the DIO pin.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 * @param[in]	Copy_u8PinID: 	1- DIO_u8PIN0
 *				              	2- DIO_u8PIN1
 *				              	3- DIO_u8PIN2
 *				              	4- DIO_u8PIN3
 *				              	5- DIO_u8PIN4
 *				              	6- DIO_u8PIN5
 *				              	7- DIO_u8PIN6
 *				              	8- DIO_u8PIN7
 *
 *
 * @return error statues
 */
ES_t DIO_enuTogglePin( u8 Copy_u8PortID , u8 Copy_u8PinID  );


/*@brief function to read the value of the DIO pin.
 *
 * @param[in]   Copy_u8PortID:	1- DIO_u8PORTA
 *								2- DIO_u8PORTB
 * 								3- DIO_u8PORTC
 *								4- DIO_u8PORTD
 *
 *				Copy_u8PinID: 	1- DIO_u8PIN0
 *				              	2- DIO_u8PIN1
 *				              	3- DIO_u8PIN2
 *				              	4- DIO_u8PIN3
 *				              	5- DIO_u8PIN4
 *				              	6- DIO_u8PIN5
 *				              	7- DIO_u8PIN6
 *				              	8- DIO_u8PIN7
 *
 * @param[out]   Copy_pu8Val:	the desired port reading.
 *
 * @return error statues
 */
ES_t DIO_enuGetPinVal( u8 Copy_u8PortID , u8 Copy_u8PinID , u8* Copy_pu8Val );


/*================= DIO pins direction options =================*/
#define DIO_u8OUTPUT  1
#define DIO_u8INPUT   0

/*=============== DIO pins value (state) options ===============*/
#define DIO_u8HIGH    1
#define DIO_u8LOW     0
#define DIO_u8FLOAT   0
#define DIO_u8PULL_UP 1


#endif /* DIO_INT_H_ */
