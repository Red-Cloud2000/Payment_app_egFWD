#include <stdio.h>
#include "Application/app.h"
#include "Server/server.h"

#include "std_types.h"


int main(void){

	//for flushing the buffer if you want(Problem in eclipse)
/*	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0); */
#if (TESTING_MODE ==0)
	uint8_t choice;
	while(1){
		printf("What do you want to do?\n");
		printf("\n");
		printf("1- New Transaction\n");
		printf("2- Show previous Transactions\n");
		printf("3- Exit (Saved data will be erased!!)\n");

		scanf("%d",&choice);
		getchar();

		switch(choice){
		case 1:
			appStart();
			break;
		case 2:
			listSavedTransactions();
			break;
		case 3:
			printf("Shutting Down...\n");
			printf("GoodBye :)\n");
			return 0;
			break;
		}
	}
#endif

#if (TESTING_MODE ==1)
	//-------------------------------card test--------------------------------------------//
/*	getCardHolderNameTest();
	getCardExpiryDateTest();
	getCardPANTest();
*/
	//-------------------------------terminal test--------------------------------------------//
/*	getTransactionDateTest();
	isCardExpriedTest();
	getTransactionAmountTest();
	isBelowMaxAmountTest();
	setMaxAmountTest();
	isValidCardPANTest();
*/
	//-------------------------------server test--------------------------------------------//
/*	recieveTransactionDataTest();
	isValidAccountTest();
	isBlockedAccountTest();
	isAmountAvailableTest();
	saveTransactionTest();
*/
	return 0;
#endif
}
