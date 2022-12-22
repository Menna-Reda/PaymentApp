#include"terminal.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("Please enter transaction date in the format DD/MM/YYYY \n");
     fflush(stdin);
	gets(termData->transactionDate);

	if (strlen(termData->transactionDate) !=10 || termData->transactionDate == NULL || termData->transactionDate[2] != '/'|| termData->transactionDate[5] != '/')
	return WRONG_DATE;
	else
    return TERMINAL_OK;

}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    if((cardData->cardExpirationDate[4]+cardData->cardExpirationDate[5])>(termData->transactionDate[9]+termData->transactionDate[10]))
        return TERMINAL_OK;
    else if((cardData->cardExpirationDate[4]+cardData->cardExpirationDate[5])==(termData->transactionDate[9]+termData->transactionDate[10]))
         if((cardData->cardExpirationDate[1]+cardData->cardExpirationDate[2])>(termData->transactionDate[3]+termData->transactionDate[4]))
          return TERMINAL_OK;
         else return EXPIRED_CARD;
    else return EXPIRED_CARD;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Please enter transaction amount \n");
	scanf("%f",&termData->transAmount);
	if(termData->transAmount<=0)
        return INVALID_AMOUNT;
    else
        return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount>termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{

    if(maxAmount<=0)
        return INVALID_AMOUNT;
    else
        termData->maxTransAmount=maxAmount;
        return TERMINAL_OK;
}
