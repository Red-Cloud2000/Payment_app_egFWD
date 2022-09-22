/*
 * server.c
 *
 *  Created on: Sep 16, 2022
 *      Author: abdoe
 */
#include <stdio.h>
#include <string.h>
#include "server.h"


uint8_t seq_no=1,account_no=0;


ST_accountsDB_t accountsDB[255]     ={
		{2000.0   , RUNNING, "8989374615436851"},
		{100000.0 , BLOCKED, "5807007076043875"},
		{15000.0  , RUNNING, "6203493828861897"},
		{200000.0 , BLOCKED, "6522847435138615"},
		{30000.0  , RUNNING, "8841727611108162"},
		{12345.0  , BLOCKED, "3001216964370998"},
		{705500.0 , RUNNING, "6369037155701133"},
		{1000.0   , BLOCKED, "6763503604627296"},
		{800.0    , RUNNING, "6224877468146186"},
		{14500.0  , RUNNING, "6362010928510773"}};

ST_transaction_t transactions[255] = {0};

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	uint8_t local_check;

	local_check = isValidAccount(&(transData->cardHolderData),&accountsDB);
	if(local_check!=0){
		printf("Request Declined: This PAN doesn't exist!!\n");
		return FRAUD_CARD;
	}
	else{
		printf("***Account matched successfully***\n");
	}
	//------------------------------------------------------------------------

	transData = &accountsDB;
	local_check = isBlockedAccount(transData);
	if(local_check!=0){
		printf("Stolen Card!!!!\n");
		return DECLINED_STOLEN_CARD;
	}
	else{
		printf("Account is running and has no issues\n");
	}
	//------------------------------------------------------------------------
	local_check = isAmountAvailable((&transData->terminalData),&accountsDB);
	if(local_check!=0){
		printf("Sorry, You don't have that cash!!\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	else{
		printf("Amount is available, wait for your cash\n");
	}


	local_check = saveTransaction(&(transData));
	if(local_check!=0){
		printf("Error while saving transaction!!\n");
		return INTERNAL_SERVER_ERROR;
	}
	else{
		printf("###Transaction have been saved successfully###\n");
	}

	accountsDB[account_no].balance -= transData->terminalData.transAmount;

	return APPROVED;

}


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	uint8_t i,j;
	uint8_t sumArray[20];
	i=0,j=0;
	accountRefrence = &accountsDB;

	while(cardData->primaryAccountNumber[i]!='\n'){
		if(cardData->primaryAccountNumber[i]!=' '){           
			sumArray[j]=cardData->primaryAccountNumber[i];
			i++;
			j++;
		}
		else{
			i++;
		}

	}

	uint8_t equal;
	for(i=0;i<10;i++){
		equal = my_strcmp(sumArray,(&accountRefrence[account_no])->primaryAccountNumber);
		if(equal==0){
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
}

uint8_t my_strcmp(uint8_t *str1,uint8_t *str2){
	uint8_t i;
	for(i=0;i<16;i++){
		if(str1[i]==str2[i]){
			continue;
		}
		else{
			return 1;
		}
	}
	return 0;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){

	if((&accountRefrence[account_no])->state!=RUNNING){
		return BLOCKED_ACCOUNT;
	}
	return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
	if(termData->transAmount > (&accountRefrence[account_no])->balance){
		return LOW_BALANCE;

	}
	return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

	transData->transactionSequenceNumber = seq_no;
	seq_no++;

	if (
			transData->transState == DECLINED_INSUFFECIENT_FUND ||
			transData->transState == DECLINED_STOLEN_CARD       ||
			transData->transState == FRAUD_CARD			            ||
			transData->transState == INTERNAL_SERVER_ERROR
	)
	{
		return SAVING_FAILED;
	}
	return SERVER_OK;
}

void listSavedTransactions(void){
/*	printf("------------------------------------------------------------\n");
	printf();
	printf();
	printf();
	printf();
	printf("------------------------------------------------------------\n");
*/
}





