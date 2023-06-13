/******************************************************************************
 *
 * Module: CONTROL
 *
 * File Name: control.h
 *
 * Description: Header file for CONTROL
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#ifndef CONTROL_H_
#define CONTROL_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MATCHED 1
#define NOT_MATCHED 0

#define READY 0x11

#define PASS_LENGTH 5
#define Max_Pass_Tries 3
#define PASSWORD_ADRESS 0x0311


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
extern uint8 App_Password[PASS_LENGTH];

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
 * Function to compare the two passwords sent by the HMI ECU.
 */
uint8 Compare_Passwords(uint8* password1,uint8* password2);
/*
 * Description :
 * Function to save the password sent by the HMI ECU in EEPROM.
 */
void Save_Pasword(uint8 *pass);
/*
 * Description :
 * Function to sent the new password by the user.
 * - receive the 2 passwords sent from the HMI ECU.
 * - compare the 2 passwords sent from the HMI ECU.
 * - store the 2 passwords sent from the HMI ECU.
 */
void Setting_Password(void);
/*
 * Description :
 * Function to receive the password from the HMI ECU via UART Driver.
 */
void Recieve_Password(uint8 *pass);
/*
 * Description :
 * Function to open the door via DC_MOTOR Driver.
 * and hold it open for 3 seconds then close it again.
 */
void OpeningDoor(void);
/*
 * Description :
 * Function to turn on the buzzer in case of a danger situation (entering wrong password 3 times)
 */
void Alert(void);

#endif /* CONTROL_H_ */
