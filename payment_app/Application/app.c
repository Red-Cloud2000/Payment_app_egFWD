/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.c
 *
 * Description: Source file for the Application module
 *
 * Author: Abdelrahman Hesham
 *
 *******************************************************************************/

#include<stdio.h>
#include<string.h>
#include "../Server/server.h"
#include "app.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
ST_terminalData_t term;
ST_transaction_t trans;
ST_cardData_t     card;

extern uint8_t savedTrans_no;

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : appStart
 *
 * [Description]   : A function to start the application and proceed in the transaction process
 *
 * [Args in]       : NONE
 * [Args out]      : NONE
 *******************************************************************************/
void appStart(void){

	if (getCardHolderName(&card)!=CARD_OK) {
		printf("Wrong name format\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid Name####\n");
	}

	if (getCardExpiryDate(&card)!=CARD_OK) {
		printf("Wrong Expiration Date format\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid Expiration Date####\n");
	}

	if (getCardPAN(&card)!=CARD_OK) {
		printf("invalid Card PAN Format\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid Card PAN Format####\n");
	}

	if (isValidCardPAN(&card)!=TERMINAL_OK ) {
		printf("invalid Card PAN\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid Card PAN####\n");
	}

	trans.cardHolderData=card;

	if (getTransactionDate(&term)!=TERMINAL_OK) {
		printf("Wrong Transaction Date format\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid Transaction Date####\n");
	}

	if (isCardExpired(&card,&term)!=TERMINAL_OK) {
		printf("expired card\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####valid card Exp. Date####\n");
	}

	if (setMaxAmount(&term,20000)!=TERMINAL_OK) {
		printf("Invalid_Maximum_Transaction_Amount!!\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####MAX amount is set####\n");
	}

	if (getTransactionAmount(&term)!=TERMINAL_OK) {
		printf("Invalid_Amount!!\n");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####Checking...####\n");
	}

	trans.terminalData=term;

	if (isBelowMaxAmount(&term)!=TERMINAL_OK) {
		printf("You have exceeded the Maximum Transaction Amount!!");
		printf("\n");
		printf("\n");
		return;
	}
	else {
		printf("####transaction accepted####\n");
	}

	if(recieveTransactionData(&trans.cardHolderData)!=SERVER_OK){
		printf("Transaction Not received!!\n");
		printf("\n");
		printf("\n");
		return;
	}
	else{
		printf("####Transaction received####\n");
		printf("\n");
		printf("\n");
		savedTrans_no++;
	}


}

//-------------------------------card test--------------------------------------------//


uint8_t card_test_count;

uint8_t name_expected_res[]={1,0,1};  // 1:WRONG_NAME , 0:CARD_OK
void getCardHolderNameTest(void){

	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : getCardHolderName\n");
	printf("1:WRONG_NAME , 0:CARD_OK\n");
	printf("=================\n");
	for(card_test_count=0;card_test_count<3;card_test_count++){
		if(card_test_count==0){
			strcpy(card.cardHolderName,"Abdelrahman\n");		}
		else if(card_test_count==1){
			strcpy(card.cardHolderName,"Abdelrahman Hesham MMM\n");		}
		else if(card_test_count==2){
			strcpy(card.cardHolderName,"Abdelrahman Hesham MMM MM\n");		}
		printf("Test Case %d:\n",card_test_count+1);
		printf("Input Data      : ");
		puts(card.cardHolderName);
		printf("Actual Result   : %d\n",getCardHolderName(&card));
		printf("Expected Result : %d\n",name_expected_res[card_test_count]);

		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}

void getCardExpiryDateTest(void){
	uint8_t card_exp_expected_res[]={2,0,2};  // 2:WRONG_EXP_DATE , 0:CARD_OK

	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : getCardExpiryDate\n");
	printf("2:WRONG_EXP_DATE , 0:CARD_OK\n");
	printf("=================\n");
	for(card_test_count=0;card_test_count<3;card_test_count++){
		if(card_test_count==0){
			strcpy(card.cardExpirationDate,"1/26");		}
		else if(card_test_count==1){
			strcpy(card.cardExpirationDate,"01/26");		}
		else if(card_test_count==2){
			strcpy(card.cardExpirationDate,"01/2026");		}
		printf("Test Case %d:\n",card_test_count+1);
		printf("Input Data      : ");
		puts(card.cardExpirationDate);
		printf("Actual Result   : %d\n",getCardExpiryDate(&card));
		printf("Expected Result : %d\n",card_exp_expected_res[card_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void getCardPANTest(void){
	uint8_t PAN_expected_res[]={3,0,3};  // 3:WRONG_PAN , 0:CARD_OK

	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : getCardPAN\n");
	printf("3:WRONG_PAN , 0:CARD_OK\n");
	printf("=================\n");
	for(card_test_count=0;card_test_count<3;card_test_count++){
		if(card_test_count==0){
			strcpy(card.primaryAccountNumber,"123345\n");		}
		else if(card_test_count==1){
			strcpy(card.primaryAccountNumber,"1234567890123452\n");		}
		else if(card_test_count==2){
			strcpy(card.primaryAccountNumber,"12345678901234521234\n");		}
		printf("Test Case %d:\n",card_test_count+1);
		printf("Input Data      : ");
		puts(card.primaryAccountNumber);
		printf("Actual Result   : %d\n",getCardPAN(&card));
		printf("Expected Result : %d\n",PAN_expected_res[card_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}



//-------------------------------terminal test--------------------------------------------//
uint8_t term_test_count;

void getTransactionDateTest(void){
	uint8_t trans_date_expected_res[]={1,0,1};  // 1:WRONG_DATE , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : getTransactionDate\n");
	printf("1:WRONG_DATE , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<3;term_test_count++){
		if(term_test_count==0){
			strcpy(term.transactionDate,"0110/2022");
		}
		else if(term_test_count==1){
			strcpy(term.transactionDate,"01/10/2022");
		}
		else if(term_test_count==2){
			strcpy(term.transactionDate,"01/10/202245");
		}
		printf("Test Case %d:\n",term_test_count+1);
		printf("Input Data      : ");
		puts(term.transactionDate);
		printf("Actual Result   : %d\n",getTransactionDate(&term));
		printf("Expected Result : %d\n",trans_date_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void isCardExpriedTest(void){
	uint8_t is_card_expired_expected_res[]={2,0,2};  // 2:EXPIRED_CARD , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isCardExpried\n");
	printf("2:EXPIRED_CARD , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<3;term_test_count++){
		if(term_test_count==0){
			strcpy(term.transactionDate    ,"01/10/2022");
			strcpy(card.cardExpirationDate ,"06/22");
		}
		else if(term_test_count==1){
			strcpy(term.transactionDate    ,"01/10/2022");
			strcpy(card.cardExpirationDate ,"12/25");
		}
		else if(term_test_count==2){
			strcpy(term.transactionDate    ,"01/10/2022");
			strcpy(card.cardExpirationDate ,"01/21");
		}
		printf("Test Case %d:\n",term_test_count+1);
		printf("Input Data       : \n");


		printf("Actual Result    : %d\n",isCardExpired(&card,&term));
		printf("Expected Result  : %d\n",is_card_expired_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void getTransactionAmountTest(void){
	uint8_t get_trans_amount_expected_res[]={4,0,4};  // 4:INVALID_AMOUNT , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : getTransactionAmount\n");
	printf("4:INVALID_AMOUNT , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<3;term_test_count++){
		if(term_test_count==0){
			term.transAmount=0.0;		}
		else if(term_test_count==1){
			term.transAmount=507.5;		}
		else if(term_test_count==2){
			term.transAmount=-200.5;		}
		printf("Test Case %d:\n",term_test_count+1);
		printf("Input           : %.3f\n",term.transAmount);
		printf("Actual Result   : %d\n",getTransactionAmount(&term));
		printf("Expected Result : %d\n",get_trans_amount_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void isBelowMaxAmountTest(void){
	uint8_t is_below_max_amount_expected_res[]={5,0,5};  // 5:EXCEED_MAX_AMOUNT , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isBelowMaxAmount\n");
	term.maxTransAmount=20000.0;
	printf("Max amount      : 20000.000\n");
	printf("5:EXCEED_MAX_AMOUNT , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<3;term_test_count++){
		if(term_test_count==0){
			term.transAmount=20001.0;		}
		else if(term_test_count==1){
			term.transAmount=2500.5;		}
		else if(term_test_count==2){
			term.transAmount=25000.0;		}
		printf("Test Case %d:\n",term_test_count+1);
		printf("Transaction amount : %.3f\n",term.transAmount);
		printf("Actual Result      : %d\n",isBelowMaxAmount(&term));
		printf("Expected Result    : %d\n",is_below_max_amount_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


float max_amount[3]={0.0,20000.000  ,-25000.0};
//wrong     ,valid      ,wrong
void setMaxAmountTest(void){
	uint8_t set_max_amount_expected_res[]={6,0,6};  // 6:INVALID_MAX_AMOUNT , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : setMaxAmount\n");
	printf("6:INVALID_MAX_AMOUNT , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<3;term_test_count++){
		printf("Test Case %d:\n",term_test_count+1);
		printf("Input           : %.3f\n",max_amount[term_test_count]);
		printf("Actual Result   : %d\n",setMaxAmount(&term,max_amount[term_test_count]));
		printf("Expected Result : %d\n",set_max_amount_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void isValidCardPANTest(void){
	uint8_t valid_PAN_expected_res[4]={3,0,0,3};  // 3:INVALID_CARD , 0:TERMINAL_OK
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isValidCardPAN\n");
	printf("3:INVALID_CARD , 0:TERMINAL_OK\n");
	printf("=================\n");
	for(term_test_count=0;term_test_count<4;term_test_count++){
		if(term_test_count==0){
			strcpy(card.primaryAccountNumber,"6203493828861896\n");
		}
		else if(term_test_count==1){
			strcpy(card.primaryAccountNumber,"6369 0371 5570 1133\n");
		}
		else if(term_test_count==2){
			strcpy(card.primaryAccountNumber,"6369037155701133\n");
		}
		else if(term_test_count==3){
			strcpy(card.primaryAccountNumber,"6203493828861892\n");
		}

		printf("Test Case %d:\n",term_test_count+1);
		printf("Input Data      : ");
		puts(card.primaryAccountNumber);
		printf("Actual Result   : %d\n",isValidCardPAN(&card));
		printf("Expected Result : %d\n",valid_PAN_expected_res[term_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}

//-------------------------------server test--------------------------------------------//
uint8_t server_test_count;

void recieveTransactionDataTest(void){
	uint8_t trans_date_expected_res[4]={3,0,2,1};  // 0:Approved
												// 1:DECLINED_INSUFFECIENT_FUND
												// 2:DECLINED_STOLEN_CARD
												// 3:FRAUD_CARD
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : recieveTransactionData\n");
	printf("1:DECLINED_INSUFFECIENT_FUND , 2:DECLINED_STOLEN_CARD , 3:FRAUD_CARD , 0:Approved\n");
	printf("=================\n");
	for(server_test_count=0;server_test_count<4;server_test_count++){
		if(server_test_count==0){
			strcpy(trans.cardHolderData.primaryAccountNumber,"1234567890123452\n");
			trans.terminalData.transAmount = 2500.0;
		}
		else if(server_test_count==1){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
			trans.terminalData.transAmount = 1500.0;		}
		else if(server_test_count==2){
			strcpy(trans.cardHolderData.primaryAccountNumber,"5807007076043875\n");
			trans.terminalData.transAmount = 2500.0;		}
		else if(server_test_count==3){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
			trans.terminalData.transAmount = 2500.0;		}
		printf("Test Case %d:\n",server_test_count+1);
		printf("Input Data: \n");
		printf("PAN                : ");
		puts(trans.cardHolderData.primaryAccountNumber);
		printf("transaction Amount : %.3f\n",trans.terminalData.transAmount);

		printf("Actual Result   : %d\n",recieveTransactionData(&trans));
		printf("Expected Result : %d\n",trans_date_expected_res[server_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void isValidAccountTest(void){
	uint8_t trans_date_expected_res[]={3,0,3};  // 3:ACCOUNT_NOT_FOUND , 0:SERVER_OK
	ST_accountsDB_t DB;
	trans.cardHolderData=card;
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isValidAccount\n");
	printf("3:ACCOUNT_NOT_FOUND , 0:SERVER_OK\n");
	printf("=================\n");
	for(server_test_count=0;server_test_count<3;server_test_count++){
		if(server_test_count==0){
			strcpy(trans.cardHolderData.primaryAccountNumber,"1234567890123452\n");
		}
		else if(server_test_count==1){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
		}
		else if(server_test_count==2){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6360667678421568\n");
		}
		printf("Test Case %d:\n",server_test_count+1);
		printf("Input Data: ");
		puts(trans.cardHolderData.primaryAccountNumber);

		printf("Actual Result   : %d\n",isValidAccount(&trans.cardHolderData,&DB));
		printf("Expected Result : %d\n",trans_date_expected_res[server_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}

void isBlockedAccountTest(void){
	uint8_t trans_date_expected_res[]={5,0,5};  // 5:BLOCKED_ACCOUNT , 0:SERVER_OK
	ST_accountsDB_t DB;
	trans.cardHolderData=card;
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isBlockedAccount\n");
	printf("5:BLOCKED_ACCOUNT , 0:SERVER_OK\n");
	printf("=================\n");
	for(server_test_count=0;server_test_count<3;server_test_count++){
		if(server_test_count==0){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6522847435138615\n");
			isValidAccount(&trans.cardHolderData,&DB);
		}
		else if(server_test_count==1){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
			isValidAccount(&trans.cardHolderData,&DB);
		}
		else if(server_test_count==2){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6763503604627296\n");
			isValidAccount(&trans.cardHolderData,&DB);
		}
		printf("Test Case %d:\n",server_test_count+1);
		printf("Input Data: ");
		puts(trans.cardHolderData.primaryAccountNumber);

		printf("Actual Result   : %d\n",isBlockedAccount(&DB));
		printf("Expected Result : %d\n",trans_date_expected_res[server_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}


void isAmountAvailableTest(void){
	uint8_t trans_date_expected_res[]={4,0,4};  // 4:LOW_BALANCE , 0:SERVER_OK
	ST_accountsDB_t DB;
	trans.cardHolderData=card;
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : isAmountAvailable\n");
	printf("4:LOW_BALANCE , 0:SERVER_OK\n");
	printf("=================\n");
	for(server_test_count=0;server_test_count<3;server_test_count++){
		if(server_test_count==0){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6522847435138615\n");
			isValidAccount(&trans.cardHolderData,&DB);
			term.transAmount = 200001.0;
		}
		else if(server_test_count==1){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
			isValidAccount(&trans.cardHolderData,&DB);
			term.transAmount = 2000.0;
		}
		else if(server_test_count==2){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6763503604627296\n");
			isValidAccount(&trans.cardHolderData,&DB);
			term.transAmount = 1200.0;
		}
		printf("Test Case %d:\n",server_test_count+1);
		printf("Input Data: ");
		puts(trans.cardHolderData.primaryAccountNumber);
		printf("transaction Amount : %.3f\n",term.transAmount);
		printf("Actual Result   : %d\n",isAmountAvailable(&term,&DB));
		printf("Expected Result : %d\n",trans_date_expected_res[server_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}

void saveTransactionTest(void){
	uint8_t trans_date_expected_res[]={1,0,1};  // 1:SAVING_FAILED , 0:SERVER_OK
	ST_accountsDB_t DB;
	trans.cardHolderData=card;
	printf("Tester Name     : Abdelrahman Hesham\n");
	printf("Function Name   : saveTransaction\n");
	printf("1:SAVING_FAILED , 0:SERVER_OK\n");
	printf("=================\n");
	for(server_test_count=0;server_test_count<3;server_test_count++){
		if(server_test_count==0){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6522847435138615\n");
			recieveTransactionData(&trans);
			trans.terminalData.transAmount = 200001.0;
		}
		else if(server_test_count==1){
			strcpy(trans.cardHolderData.primaryAccountNumber,"8989374615436851\n");
			trans.terminalData.transAmount = 2000.0;
			recieveTransactionData(&trans);
		}
		else if(server_test_count==2){
			strcpy(trans.cardHolderData.primaryAccountNumber,"6763503604627296\n");
			trans.terminalData.transAmount = 1200.0;
			recieveTransactionData(&trans);
		}
		printf("Test Case %d:\n",server_test_count+1);
		printf("Input Data: ");
		puts(trans.cardHolderData.primaryAccountNumber);

		printf("Actual Result   : %d\n",saveTransaction(&trans));
		printf("Expected Result : %d\n",trans_date_expected_res[server_test_count]);
		printf("=================\n");
	}
	printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	printf("\n");
}



