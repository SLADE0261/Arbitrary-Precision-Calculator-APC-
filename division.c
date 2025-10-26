/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"

int division(Dlist **dividendHead, Dlist **dividendTail, Dlist **divisorHead, Dlist **divisorTail, Dlist **resultHead, Dlist **resultTail)
{
	int dividendLength, divisorLength;
	int quotient = 0, nonZeroDigits = 0;

	// Calculate divisor length and check for zero
	Dlist *tempDivisor = *divisorHead;
	divisorLength = 0;

	while (tempDivisor != NULL)
	{
		divisorLength++;
		if (tempDivisor->data != 0)
		{
			nonZeroDigits++;
		}
		tempDivisor = tempDivisor->next;
	}

	// Check for division by zero
	if (nonZeroDigits == 0)
	{
		printf("Error: Divisor is empty list. Division by zero is not allowed.\n");
		return FAILURE;
	}

	// Perform repeated subtraction to find quotient
	while (1)
	{
		// Calculate current dividend length
		Dlist *tempDividend = *dividendHead;
		dividendLength = 0;

		while (tempDividend != NULL)
		{
			dividendLength++;
			tempDividend = tempDividend->next;
		}

		// Compare lengths first for efficiency
		if (dividendLength > divisorLength)
		{
			// Dividend is definitely larger, subtract divisor
			subtraction(dividendHead, dividendTail, divisorHead, divisorTail, resultHead, resultTail);
			dl_delete_list(dividendHead, dividendTail);
			*dividendHead = *resultHead;
			*dividendTail = *resultTail;
			*resultHead = *resultTail = NULL;
			quotient++;
		}
		else if (dividendLength < divisorLength)
		{
			// Dividend is smaller, division complete
			break;
		}
		else // If lengths equal, compare digit by digit
		{
			tempDividend = *dividendHead;
			tempDivisor = *divisorHead;
			while (tempDividend != NULL && tempDivisor != NULL)
			{
				if (tempDividend->data > tempDivisor->data) // dividend > divisor
				{
					// Perform subtraction and increment quotient
					subtraction(dividendHead, dividendTail, divisorHead, divisorTail, resultHead, resultTail);
					dl_delete_list(dividendHead, dividendTail);
					*dividendHead = *resultHead;
					*dividendTail = *resultTail;
					*resultHead = *resultTail = NULL;
					quotient++;
					break;
				}
				else if (tempDividend->data < tempDivisor->data)
				{
					printf("\nQuotient: %d\n", quotient);
					return SUCCESS;
				}
				tempDividend = tempDividend->next;
				tempDivisor = tempDivisor->next;
			}
			// If all digits equal, numbers are equal
			if (tempDividend == NULL && tempDivisor == NULL)
			{
				quotient++;
				break;
			}
		}
	}
	// Print final quotient
	printf("%d\n", quotient);
	return SUCCESS;
}