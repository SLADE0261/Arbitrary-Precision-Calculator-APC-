/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */

	// Start from least significant digits (tail nodes)
	Dlist * temp1 = *tail1;
	Dlist * temp2 = *tail2;

	int digi_num1;
	int digi_num2;
	
	int result_num = 0;

	int borrow = 0; // For handling borrowing in subtraction

	// Process digits from right to left
	while (temp1 != NULL || temp2 != NULL)
	{
		// Get digits, treating NULL as 0
		if (temp1 != NULL)
			digi_num1 = (temp1->data);
		else
			digi_num1 = 0;

		if (temp2 != NULL)
			digi_num2 = (temp2->data);
		else
			digi_num2 = 0;

		// Apply borrow from previous subtraction
		if (borrow == 1)
		{
			digi_num1--;
			borrow = 0;
		}
		
		// Handle borrowing when minuend digit is smaller
		if (digi_num1 >= digi_num2)
		{
			result_num = digi_num1 - digi_num2;
		}
		else
		{
			digi_num1 = digi_num1 + 10; // Borrow from next digit
			borrow = 1;
			result_num = digi_num1 - digi_num2;
		}

		// Insert result digit at the beginning
		dl_insert_first(headR, tailR, result_num);
		
		// Move to next higher-order digits
		if (temp1 != NULL)
			temp1 = temp1->prev;

		if (temp2 != NULL)
			temp2 = temp2->prev;
	}
	
	// Remove leading zeros from result
	while ((*headR)->data == 0 && (*headR)->next != NULL)
	{
		dl_delete_first(headR, tailR);
	}

	return 0;
}