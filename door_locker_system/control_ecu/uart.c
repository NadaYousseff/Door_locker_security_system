 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author:  Nada Youssef
 *
 *******************************************************************************/
#include "uart.h"
#include "common_macros.h"
#include <avr/io.h>


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void UART_init(const UART_ConfigType * Config_Ptr){
	uint16 ubrr_value = 0;

	/* Double transmission speed */
	UCSRA=(1<<U2X);
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = (Config_Ptr->bit_data)>>2) For data bits mode
	 *   "the shift operation to get the value of UCSZ2 only (MSB in 3-bit number) without UCSZ1 and UCSZ0"
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB=(1<<RXEN)|(1<<TXEN)|(((Config_Ptr->bit_data)>>2)<<UCSZ2);
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = (Config_Ptr->parity) for parity mode
	 * USBS    = (Config_Ptr->stop_bit) for stop bit
	 * UCSZ1:0 =  ((Config_Ptr->bit_data)&0x03) For data bits mode
	 *   "the & operation to get the value of UCSZ1 and UCSZ0 0nly without UCSz2"
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | (Config_Ptr->parity)<<UPM0 | (Config_Ptr->stop_bit)<<USBS | ((Config_Ptr->bit_data)&0x03)<<UCSZ0;

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
