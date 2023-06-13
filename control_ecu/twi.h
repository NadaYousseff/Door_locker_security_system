/******************************************************************************
 *
 * Module: TWI
 *
 * File Name: twi.h
 *
 * Description: Header file for the AVR TWI driver
 *
 * Author:  Nada Youssef
 *
 *******************************************************************************/

#ifndef TWI_H_
#define TWI_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef uint8 TWI_Address;
typedef uint32 TWI_BaudRate;

typedef struct{
	TWI_Address address;
	TWI_BaudRate bit_rate;
}TWI_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the TWI by:
 * 1. Setup the Bit Rate of TWI.
 * 2. Setup the Address of the device in salve mode.
 * 3. Enable the TWI.
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);
/*
 * Description :
 * Functional responsible for sending the start bit
 */
void TWI_start(void);
/*
 * Description :
 * Functional responsible for sending the stop bit
 */
void TWI_stop(void);
/*
 * Description :
 * Functional responsible for sending the data (1 Byte) by the TWI
 */
void TWI_writeByte(uint8 data);
/*
 * Description :
 * Functional responsible for receiving the data (1 Byte) by the TWI
 *  and sending ACK after reading.
 */
uint8 TWI_readByteWithACK(void);
/*
 * Description :
 * Functional responsible for receiving the data (1 Byte) by the TWI
 */
uint8 TWI_readByteWithNACK(void);
/*
 * Description :
 * Functional responsible for getting the status of the TWI
 */
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
