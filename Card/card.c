#include "card.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool alphabet(ST_cardData_t* cardData)
{
   for (int i = 0; i <= strlen(cardData->cardHolderName); i++) {
        if (!(( cardData->cardHolderName[i] >= 'a' && cardData->cardHolderName[i] <= 'z')
              || (cardData->cardHolderName[i] >= 'A' && cardData->cardHolderName[i] <= 'Z')
              || cardData->cardHolderName[i] == ' '))
             return false;

        else
             i++;
}
return true;

   }


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	printf("Please enter card holder's name\n");
     fflush(stdin);
	gets(cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 || cardData->cardHolderName == NULL||alphabet(cardData)==false)

		{

		    return WRONG_NAME;
		    }
	else
		{

		    return CARD_OK;
        }

}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

	printf("Please enter card expiry date in the format 'MM/YY'\n");
	fflush(stdin);
	gets(cardData->cardExpirationDate);



	if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate == NULL || cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter card Primary Account Number\n");
	fflush(stdin);
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || cardData->primaryAccountNumber == NULL)

		return WRONG_PAN;

	else

		return CARD_OK;
}

