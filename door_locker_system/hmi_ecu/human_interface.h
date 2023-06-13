/******************************************************************************
 *
 * Module: HUMAN_INTERFACE
 *
 * File Name: human_interface.h
 *
 * Description: Header file for HUMAN_INTERFACE
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#ifndef HUMAN_INTERFACE_H_
#define HUMAN_INTERFACE_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MATCHED 1
#define NOT_MATCHED 0

#define READY 0x11

#define PASS_LENGTH 5

#define Open_Door_Option '+'
#define Change_Password_Option '-'

#define Opening_Door 10
#define Changing_Password 20
#define Danger 91

#define DOOR_OPENNING_TIME	15   //seconds
#define DOOR_CLOSING_TIME	15   //seconds
#define DOOR_LEFT_OPEN_TIME	3    //seconds
#define DANGER_TIME 60           //seconds
/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/
extern uint32 g_ticks;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function to call in Timer1 ISR.
 */
void CallBack_Function(void);
/*
 * Description :
 * Function to get the password of the user for the first time.
 */
void Get_Password(uint8 *pass);
/*
 * Description :
 * Function to get the password of the user for the second time for confirmation.
 */
void Get_Password_again(uint8 *pass);
/*
 * Description :
 * Function to send the password to the control ECU via UART Driver.
 */
void Send_Password(uint8 *pass);
/*
 * Description :
 * Function to get the password from user twice for confirmation.
 * send it to the control ECU.
 * and inform the user whether the two password are matched or not.
 */
void Set_Password(void);
/*
 * Description :
 * Function to display the options for the user on the LCD.
 */
void Display_Options(void);
/*
 * Description :
 * Function to display the opening statues to the user
 * while the control ECU is opening the door.
 */
void OpeningDoor(void);
/*
 * Description :
 * Function to display the Danger situation to the user on LCD.
 */
void Display_Danger(void);
/*
 * Description :
 * Function to display to the user that the password doesn't match.
 */
void Display_MisMatch(void);

#endif /* HUMAN_INTERFACE_H_ */
