/*
 * card.c
 *
 *  Created on: Sep 16, 2022
 *      Author: abdoe
 */

#include <stdio.h>
#include <string.h>
#include "card.h"

#define CARD_HOLDER_NAME_SIZE             50
#define CARD_PRIMARY_ACCOUNT_NUMBER_SIZE  21

#define CARD_HOLDER_NAME_MAX_LENGTH       24
#define CARD_HOLDER_NAME_MIN_LENGTH       20
#define EXPIRY_DATE_MAX_LENGTH            5
#define EXPIRY_DATE_MIN_LENGTH            5
#define PAN_MAX_LENGTH                    19
#define PAN_MIN_LENGTH                    16

uint8_t length;

uint8_t pan_length;



EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	if(cardData == NULL){
		return WRONG_NAME;
	}
	uint8_t check;
	printf("Please Enter The Card-Holder name: ");
	do{
		fgets(cardData->cardHolderName,CARD_HOLDER_NAME_SIZE,stdin);             //getting array input from user using fgets to include spaces
		length = strlen(cardData->cardHolderName)-1;
		check = Max_OR_Min(length,CARD_HOLDER_NAME_MAX_LENGTH,CARD_HOLDER_NAME_MIN_LENGTH);

		switch(check){
		case LESS:
			printf("The Name length is less than the minimum(20 Letters), Please try gain: ");
			break;
		case MORE:
			printf("The Name length is more than the maximum(24 Letters), Please try gain: ");
			break;
		}

	}
	while(check!=1);

	if(0==check){
		check = WRONG_NAME;
	}
	else if(1==check){
		check = CARD_OK;
	}
	return check;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	if(cardData == NULL){
		return WRONG_EXP_DATE;
	}
	uint8_t check,i;
	printf("Please Enter The Card Expiry Date (MM/YY): ");
	do{
		scanf("%s",&cardData->cardExpirationDate);
		getchar();
		length = strlen(cardData->cardExpirationDate);
		printf("Length = %d\n",length);
		check = Max_OR_Min(length,EXPIRY_DATE_MAX_LENGTH,EXPIRY_DATE_MIN_LENGTH);

		switch(check){
		case LESS:
			printf("The Card E Date length is less than the minimum(5 characters), Please try gain: ");
			break;
		case MORE:
			printf("The Card E Date length is more than the maximum(5 characters), Please try gain: ");
			break;
		}

	}
	while(check!=1);

	if(
			(cardData->cardExpirationDate[0]>='0'&&cardData->cardExpirationDate[0]<='9') &&
			(cardData->cardExpirationDate[1]>='0'&&cardData->cardExpirationDate[1]<='9') &&
			(cardData->cardExpirationDate[2]==      '/'       ) &&
			(cardData->cardExpirationDate[3]>='0'&&cardData->cardExpirationDate[3]<='9') &&
			(cardData->cardExpirationDate[4]>='0'&&cardData->cardExpirationDate[4]<='9')
	){
		check = CARD_OK;
	}
	else{
		check = WRONG_EXP_DATE;
	}
	return check;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	if(cardData == NULL){
		return WRONG_PAN;
	}
	uint8_t check , i;
	printf("Please Enter The Card PAN: ");

	fgets(cardData->primaryAccountNumber,CARD_PRIMARY_ACCOUNT_NUMBER_SIZE,stdin);             //getting array input from user using fgets to include spaces

	pan_length = strlen(cardData->primaryAccountNumber)-1;
	check = Max_OR_Min(pan_length,PAN_MAX_LENGTH,PAN_MIN_LENGTH);

	switch(check){
	case LESS:
		printf("The PAN length is less than the minimum(16 characters), Please try gain: ");
		return WRONG_PAN;
		break;
	case MORE:
		printf("The PAN length is more than the maximum(19 characters), Please try gain: ");
		return WRONG_PAN;
		break;
	}
	return CARD_OK;
}


uint8_t Max_OR_Min(uint8_t len,uint8_t Max, uint8_t Min){
	if(len<Min){
		return LESS;
	}
	else if(len>Max){
		return MORE;
	}
	else{
		return 1;
	}
}
