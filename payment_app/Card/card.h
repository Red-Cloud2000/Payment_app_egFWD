/*
 * card.h
 *
 *  Created on: Sep 16, 2022
 *      Author: abdoe
 */

#ifndef CARD_H_
#define CARD_H_

#include "../std_types.h"

#define LESS         55
#define MORE         65

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

uint8_t Max_OR_Min(uint8_t len,uint8_t Max, uint8_t Min);

uint8_t checkSum(uint8_t *pan);



#endif /* CARD_H_ */
