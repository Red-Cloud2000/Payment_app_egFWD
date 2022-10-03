/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.h
 *
 * Description: Header file for the Application module
 *
 * Author: Abdelrahman Hesham
 *
 *******************************************************************************/
#ifndef APP_H_
#define APP_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function to start the application and proceed in the transaction process
 *
 */
void appStart(void);

//-------------------------------card test--------------------------------------------//
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

//-------------------------------terminal test--------------------------------------------//
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

//-------------------------------server test--------------------------------------------//
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);

#endif /* APP_H_ */
