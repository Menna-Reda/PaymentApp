#include "app.h"
void appStart(void)
{
	 ST_cardData_t cardData;
	 ST_terminalData_t termData;
	 ST_transaction transaData;
	 float maxAmount=10000.0;


    transaData.terminalData = termData;
setMaxAmount(&transaData.terminalData,maxAmount);
    if (getCardHolderName(&transaData.cardHolderData) == WRONG_NAME)
	 {
		 printf("WRONG NAME \n");
		 return;
	 }

    else if (getCardExpiryDate(&transaData.cardHolderData) == WRONG_EXP_DATE)
	 {
		 printf("WRONG EXP DATE \n");
		 return;
	 }
	 else if (getCardPAN(&transaData.cardHolderData) == WRONG_PAN)
	 {
		 printf("wRONG PAN \n");
		 return;
	 }
	 else if(getTransactionDate(&transaData.terminalData)==WRONG_DATE)
     {
         printf("WRONG DATE \n");
		 return;
     }
     else if(isCardExpired(&transaData.cardHolderData,&transaData.terminalData)==EXPIRED_CARD)
     {
         printf("EXPIRED CARD \n");
		 return;
     }
     else if(getTransactionAmount(&transaData.terminalData)==INVALID_AMOUNT)
     {
         printf("INVALID AMOUNT \n");
		 return;
     }
     else if(isBelowMaxAmount(&transaData.terminalData)==EXCEED_MAX_AMOUNT)
    {
         printf("EXCEED MAX AMOUNT \n");
		 return;
    }
     else if(recieveTransactionData(&transaData)==DECLINED_STOLEN_CARD)
    {
         printf("DECLINED STOLEN CARD \n");
         saveTransaction(&transaData);
          listSavedTransactions();
		 return;
    }
      else if(recieveTransactionData(&transaData)==INTERNAL_SERVER_ERROR)
    {
         printf("INTERNAL SERVER ERROR \n");
         saveTransaction(&transaData);
          listSavedTransactions();
		 return;
    }

    else if(recieveTransactionData(&transaData)==FRAUD_CARD)
    {
         printf("Account not found \n");
          saveTransaction(&transaData);
           listSavedTransactions();
		 return;
    }
     else if(recieveTransactionData(&transaData)==DECLINED_INSUFFECIENT_FUND)
    {
         printf("DECLINED INSUFFECIENT FUND \n");
          saveTransaction(&transaData);
           listSavedTransactions();
		 return;
    }
    else
    {

saveTransaction(&transaData);

         printf("transaction is Approved \n\n\n");
          saveTransaction(&transaData);
         listSavedTransactions();
    }



}
