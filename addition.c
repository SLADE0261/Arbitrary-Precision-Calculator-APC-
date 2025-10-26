/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */

	// Start from least significant digits (tail nodes)
	Dlist * temp1 = *tail1;
	Dlist * temp2 = *tail2;
	
	int digi_num1;
	int digi_num2;
	
	int result_num = 0;

	int carry = 0; // For handling carry in addition

	// Continue until all digits and carry are processed
	while (temp1 != NULL || temp2 != NULL || carry != 0)
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

		// Add digits and carry
		result_num = digi_num1 + digi_num2 + carry;
		carry = result_num / 10; // Calculate new carry
		dl_insert_first(headR, tailR, result_num%10); // Store only units digit
		
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
