/*
 * main.c
 *
 *  Created on: Sep 16, 2022
 *      Author: abdoe
 */

#include <stdio.h>
#include "Card/card.h"
#include "Terminal/terminal.h"
#include "Server/server.h"

int main()
{

ST_terminalData_t term;
ST_cardData_t     card;
ST_accountsDB_t  accountDB;
ST_transaction_t trans;
printf("card return %d\n",getCardHolderName(&card));
printf("card return %d\n",getCardPAN(&card));

printf("setMaxAmount return %d\n",setMaxAmount(&term,20000));
printf("get trans return %d\n",getTransactionAmount(&term));
printf("is belowmax return %d\n",isBelowMaxAmount(&term));

printf("card return %d\n",getCardExpiryDate(&card));

printf("transaction date return %d\n",getTransactionDate(&term));

if (isCardExpired(&card,&term)!=0) {
	printf("expired card \n");
}
else {
	printf("valid card \n");
}



if (isBelowMaxAmount(&term)!=0) {
	printf("You have exceeded the Maximum Transaction Amount!!");
}
else {
	printf("transaction accepted \n");
}


if (isValidCardPAN(&card)!=0) {
	printf("invalid card pan \n");
}
else {
	printf("valid card pan \n");
}

if(recieveTransactionData(&trans)!=0){
	printf("Transaction Not received!!\n");
}
else{
	printf("##Transaction received###\n");
}

return 0;
}
