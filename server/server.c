#include "server.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 ST_accountsDB_t accountsDB[255]={{2000.0, RUNNING, "8989374615436851"},{50000.0,RUNNING,"5435688937461198"},{7000.0, RUNNING, "2035900037485468"},
 {100000.0, RUNNING, "5002015613006120"},
 {20000.0, RUNNING, "8893374620036374"},
 {100000.0, BLOCKED, "5807007076043875"},
 {50000.0, BLOCKED, "5015003036222879"},
 {90000.0, RUNNING, "6342011981003150"},
 {3000.0, BLOCKED, "5613888026340561"},
 {1000.0, BLOCKED, "8935773036374846"},
 };
uint32_t transactionSequenceNumber=0;
ST_transaction transactionsDB[255]={};
 ST_accountsDB_t *accountRefrence;

EN_transStat_t state;
EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
    if(isValidAccount(&transData->cardHolderData)==ACCOUNT_NOT_FOUND)
    {transData->transState=FRAUD_CARD;

        return FRAUD_CARD;}
    else if(isAmountAvailable(&transData->terminalData)==LOW_BALANCE)
        {   transData->transState=DECLINED_INSUFFECIENT_FUND;

            return DECLINED_INSUFFECIENT_FUND;}
    else if(isBlockedAccount()==BLOCKED_ACCOUNT)
        {transData->transState=DECLINED_STOLEN_CARD;

            return DECLINED_STOLEN_CARD;
            }
    else if(transactionSequenceNumber==255)
      {transData->transState=INTERNAL_SERVER_ERROR;

          return INTERNAL_SERVER_ERROR;}
    else {
            transData->transState=APPROVED;
            return APPROVED;}

}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{

     for(int i=0;i<=255;i++)
    {
       if(strcmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber) == 0)
         {
          accountRefrence=&accountsDB[i];
           return SERVER_OK;
         }

    }
accountRefrence=NULL;
return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount()
{
    if(accountRefrence->state==BLOCKED)
        return BLOCKED_ACCOUNT;
    else
        return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if(termData->transAmount<= accountRefrence->balance)

        return   SERVER_OK;
    else
        return LOW_BALANCE;

}

EN_serverError_t saveTransaction(ST_transaction *transData)
{
    if (transactionSequenceNumber >= 255)
			return SAVING_FAILED;
		else {
            transactionsDB[transactionSequenceNumber].cardHolderData = transData->cardHolderData;
			transactionsDB[transactionSequenceNumber].terminalData = transData->terminalData;
			transactionsDB[transactionSequenceNumber].transState = transData->transState;
			transactionsDB[transactionSequenceNumber].transactionSequenceNumber = transactionSequenceNumber;
			transactionsDB[transactionSequenceNumber].transState = transData->transState;
             transactionSequenceNumber++;
                return SERVER_OK;
			}
}


void listSavedTransactions(void){

 uint32_t num= transactionSequenceNumber-1;
printf("#########################\n");
        printf("Transaction Sequence Number:%u\n",num);
        printf("Transaction Date:%s\n",transactionsDB[num].terminalData.transactionDate);
        printf("Transaction Amount:%f\n",transactionsDB[num].terminalData.transAmount);

            if(transactionsDB[num].transState==APPROVED)
               {
                 printf("Transaction State:APPROVED\n");
                  printf("Your previous balance=%f\n",accountRefrence->balance);


                printf("Your current balance=%f\n",accountRefrence->balance-=transactionsDB[num].terminalData.transAmount);
               }
            else if(transactionsDB[num].transState==DECLINED_INSUFFECIENT_FUND)
                printf("Transaction State:DECLINED_INSUFFECIENT_FUND\n");
            else if(transactionsDB[num].transState==DECLINED_STOLEN_CARD)
                printf("Transaction State:DECLINED_STOLEN_CARD\n");
            else if(transactionsDB[num].transState==FRAUD_CARD)
                printf("Transaction State:FRAUD_CARD\n");
            else if(transactionsDB[num].transState==INTERNAL_SERVER_ERROR)
                printf("Transaction State:INTERNAL_SERVER_ERROR\n");

        printf("Terminal Max Amount:%f\n",transactionsDB[num].terminalData.maxTransAmount);
        printf("Cardholder Name:%s\n", transactionsDB[num].cardHolderData.cardHolderName);
        printf("PAN:%s\n",transactionsDB[num].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date:%s\n",transactionsDB[num].cardHolderData.cardExpirationDate);
        printf("#########################\n");

}



