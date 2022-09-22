/*
 * terminal.c
 *
 *  Created on: Sep 16, 2022
 *      Author: abdoe
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "terminal.h"
#include "../Card/card.h"

#define TRANSACTION_DATE_MAX_LENGTH    10
#define TRANSACTION_DATE_MIN_LENGTH    10

extern uint8_t length;
extern uint8_t pan_length;


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	if(termData == NULL){
		return WRONG_DATE;
	}
	uint8_t check,i;
	printf("Please Enter The Transaction Date(DD/MM/YYYY, e.g 25/06/2022) : ");
	do{
		scanf("%s",&termData->transactionDate);
		getchar();
		length = strlen(termData->transactionDate);
		check = Max_OR_Min(length,TRANSACTION_DATE_MAX_LENGTH,TRANSACTION_DATE_MIN_LENGTH);

		switch(check){
		case LESS:
			printf("The Date length is less than the minimum(10 chars), Please try gain: ");
			break;
		case MORE:
			printf("The Date length is more than the maximum(10 chars), Please try gain: ");
			break;
		}
	}
	while(check!=1);

	if(
			(termData->transactionDate[0] >='0' && termData->transactionDate[0] <='9')   &&
			(termData->transactionDate[1] >='0' && termData->transactionDate[1] <='9')   &&
			(termData->transactionDate[2] == '/'                                     )   &&
			(termData->transactionDate[3] >='0' && termData->transactionDate[3] <='9')   &&
			(termData->transactionDate[4] >='0' && termData->transactionDate[4] <='9')   &&
			(termData->transactionDate[5] == '/'                                     )	 &&
			(termData->transactionDate[6] >='0' && termData->transactionDate[6] <='9')   &&
			(termData->transactionDate[7] >='0' && termData->transactionDate[7] <='9')   &&
			(termData->transactionDate[8] >='0' && termData->transactionDate[8] <='9')   &&
			(termData->transactionDate[9] >='0' && termData->transactionDate[9] <='9')

	){
		return TERMINAL_OK;
	}
	else{
		printf("WRONG_DATE Format\n");
		return WRONG_DATE;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
	if(cardData == NULL || termData==NULL){
		return EXPIRED_CARD;
	}

	uint8_t trans_year_val;
	uint8_t card_year_val;

	uint8_t trans_month_val;
	uint8_t card_month_val;

	uint8_t trans_year[2];
	trans_year[0]=termData->transactionDate[8];
	trans_year[1]=termData->transactionDate[9];

	uint8_t card_year[2];
	card_year[0]=cardData->cardExpirationDate[3];
	card_year[1]=cardData->cardExpirationDate[4];

	uint8_t trans_month[2];
	trans_month[0]=termData->transactionDate[3];
	trans_month[1]=termData->transactionDate[4];

	uint8_t card_month[2];
	card_month[0]=cardData->cardExpirationDate[0];
	card_month[1]=cardData->cardExpirationDate[1];


	trans_year_val = atoi(trans_year);
	card_year_val  = atoi(card_year);


	trans_month_val = atoi(trans_month);
	card_month_val = atoi(card_month);


	if(card_year_val>trans_year_val || ((card_year_val-trans_year_val)==0 && (card_month_val-trans_month_val)>0)){
		return TERMINAL_OK;
	}
	else{
		return EXPIRED_CARD;
	}
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	printf("Please Enter The Transaction amount (not less than 1): ");
	scanf("%f",&termData->transAmount);

	if(termData->transAmount<=0){
		printf(" Invalid_Amount!!\n");
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	if(termData->transAmount > termData->maxTransAmount){
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){

	if(maxAmount<=0){
		printf(" Invalid_Maximum_Transaction_Amount!!\n");
		return INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = maxAmount;
	return TERMINAL_OK;
}


EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

	uint8_t i,j=0,sum=0;
	uint16_t res,Check_SumNumber;
	uint8_t sumArray[20];
	uint8_t pan_no_space_length=0;


	i=0;
	while(cardData->primaryAccountNumber[i]!='\n'){
		if(((cardData->primaryAccountNumber[i]>='0') && (cardData->primaryAccountNumber[i]<='9'))){
			pan_no_space_length++;
			i++;
		}
		else{
			i++;
			continue;
		}
	}
	printf("\n");
  
	i=0;
	while(cardData->primaryAccountNumber[i]!='\n'){
		if(cardData->primaryAccountNumber[i]!=' '){            //240 = ' '
			sumArray[j]=cardData->primaryAccountNumber[i];
			i++;
			j++;
		}
		else{
			i++;
		}

	}



	i=0;
	while(cardData->primaryAccountNumber[i]!='\0'){
			sumArray[i]=cardData->primaryAccountNumber[i]-48;

		i++;
	}

	printf("\n");
  
	i=0;
	while(i<16){
		if((i+1)%2!=0){
			sumArray[i]*=2;
			if(sumArray[i]>=10){
				sum=sumArray[i]%10+sumArray[i]/10;
				sumArray[i]=sum;
			}
			i++;
			j++;
		}
		else{
			i++;
			j++;
		}
	}
	res=arraySum(sumArray,15);
	Check_SumNumber=((res*9)%10);

	if(pan_no_space_length!=16 || Check_SumNumber!=cardData->primaryAccountNumber[pan_length-1]-48){
		return INVALID_CARD;
	}
	return TERMINAL_OK;


}

uint8_t arraySum(uint8_t *arr,uint8_t size){
	uint8_t i=0,sum=0;
	while(i<size){
		sum+=arr[i];
		i++;
	}
	return sum;

}
