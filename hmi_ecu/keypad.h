/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: Header file for the keypad driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define STANDARD_KEYPAD				FALSE
#define KEYPAD_NUM_COL				4
#define KEYPAD_NUM_ROW				4

#define KEYPAD_ROW_PORT_ID			PORTB_ID
#define KEYPAD_COL_PORT_ID			PORTB_ID

#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID

#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED		LOGIC_HIGH



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*--------------------------------------------------------------------------------
  [Function Name]:         KEYPAD_init

  [Description]:           Function to initialize keypad pins

  [Arguments]:             VOID

  [Returns]:               VOID
 ---------------------------------------------------------------------------------*/

void KEYPAD_init(void);

/*--------------------------------------------------------------------------------
  [Function Name]:         KEYPAD_getPressedKey

  [Description]:           Get the Keypad pressed button

  [Arguments]:             VOID

  [Returns]:               button pressed
 ---------------------------------------------------------------------------------*/

uint8 KEYPAD_getPressedKey (void);

#endif /* KEYPAD_H_ */

