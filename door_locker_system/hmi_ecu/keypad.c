/******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.c
 *
 * Description: Source file for the keypad driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#include "keypad.h"
#include "common_macros.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if (STANDARD_KEYPAD == FALSE)

#if (KEYPAD_NUM_COL == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 buttonNumber);
#elif(KEYPAD_NUM_COL == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 buttonNumber);

#endif
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void KEYPAD_init()
{
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_INPUT);
#if(KEYPAD_NUM_COL == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif

	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, LOGIC_HIGH);
	GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);
#if(KEYPAD_NUM_COL == 4)
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, LOGIC_HIGH);
#endif
}

uint8 KEYPAD_getPressedKey()
{
	uint8 col,row;
	while(1)
	{
		for(row = 0 ; row < KEYPAD_NUM_ROW ; row++)
		{
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col = 0 ; col < KEYPAD_NUM_COL ; col++)
			{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
					#if (STANDARD_KEYPAD == FALSE)
						#if (KEYPAD_NUM_COL == 3)
							GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
							return KEYPAD_4x3_adjustKeyNumber( (row*KEYPAD_NUM_COL)+col+1 );
						#elif (KEYPAD_NUM_COL == 4)
							GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
							return KEYPAD_4x4_adjustKeyNumber( (row*KEYPAD_NUM_COL)+col+1 );
						#endif
					#elif (STANDARD_KEYPAD == TRUE)
						GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
						return ((row*KEYPAD_NUM_COL)+col+1);
					#endif /* ---> STANDARD_KEYPAD */
				}
			}

			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_INPUT);
		}
	}
}

#if (STANDARD_KEYPAD == FALSE)

#if (KEYPAD_NUM_COL == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 10:
		keypad_button = '*';
		break;
	case 11:
		keypad_button = 0;
		break;
	case 12:
		keypad_button = '#';
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COL == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch (button_number)
	{
	case 1:
		keypad_button = 7;
		break;
	case 2:
		keypad_button = 8;
		break;
	case 3:
		keypad_button = 9;
		break;
	case 4:
		keypad_button = '%';
		break;
	case 5:
		keypad_button = 4;
		break;
	case 6:
		keypad_button = 5;
		break;
	case 7:
		keypad_button = 6;
		break;
	case 8:
		keypad_button = '*';
		break;
	case 9:
		keypad_button = 1;
		break;
	case 10:
		keypad_button = 2;
		break;
	case 11:
		keypad_button = 3;
		break;
	case 12:
		keypad_button = '-';
		break;
	case 13:
		keypad_button = 13;
		break;
	case 14:
		keypad_button = 0;
		break;
	case 15:
		keypad_button = '=';
		break;
	case 16:
		keypad_button = '+';
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}

#endif

#endif	/* STANDARD_KEYPAD */
