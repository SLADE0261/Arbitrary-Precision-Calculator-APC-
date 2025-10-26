// /*******************************************************************************************************************************************************************
// *Title			: Multiplication
// *Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
// *Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
// *Input Parameters	: head1: Pointer to the first node of the first double linked list.
// 			: tail1: Pointer to the last node of the first double linked list.
// 			: head2: Pointer to the first node of the second double linked list.
// 			: tail2: Pointer to the last node of the second double linked list.
// 			: headR: Pointer to the first node of the resultant double linked list.
// *Output			: Status (SUCCESS / FAILURE)
// *******************************************************************************************************************************************************************/

#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */

	// Start from least significant digits (tail nodes)
	Dlist * temp1 = *tail1;
	Dlist * temp2 = *tail2;
	
	Dlist *headR1 = NULL, *tailR1 = NULL;
	Dlist *headR2 = NULL, *tailR2 = NULL;

	int digi_num1;
	int digi_num2;
	
	int result_num = 0;
	int zero_count = 0; // For positional multiplication (10^n)
	int carry = 0;

	int first_addition = 1;

	// Multiply each digit of second number with entire first number
	while (temp2)
	{
		// Add zeros for positional value (ones, tens, hundreds, etc.)
		for (int i=0; i<zero_count; i++)
		{
			dl_insert_first(&headR2, &tailR2, 0);
		}

		carry = 0;

		// Multiply current digit of second number with all digits of first number
		while (temp1 || carry)
		{
			if (temp1)
			{
				result_num = temp1->data * temp2->data + carry;
				temp1 = temp1->prev;
			} else
			{
				result_num = carry;
			}

			// Handle carry and remainder
			carry = result_num / 10;
			result_num = result_num % 10;
			
			// Always insert into headR2 for current row
			dl_insert_first(&headR2, &tailR2, result_num);
		}		
		
		// For first multiplication, just store the result
		if (first_addition == 1)
		{
			// For first iteration, just copy the result
			*headR = headR2;
			*tailR = tailR2;
			first_addition = 0;
		}
		else
		{
			// Add current partial product to accumulated result
			// Set headR1 to current result for addition
			headR1 = *headR;
			tailR1 = *tailR;
			
			// Initialize result to NULL before addition
			*headR = NULL;
			*tailR = NULL;
			
			addition(&headR1, &tailR1, &headR2, &tailR2, headR, tailR);
			
			// Clean up temporary lists
			dl_delete_list(&headR1, &tailR1);
			dl_delete_list(&headR2, &tailR2);
			
			// Reset for next iteration
			headR1 = NULL;
			tailR1 = NULL;
		}
		
		// Reset headR2 and tailR2 for next iteration
		headR2 = NULL;
		tailR2 = NULL;
		
		// Move to next digit in second number
		temp2 = temp2->prev;
		temp1 = *tail1;
		zero_count++;
	}

	// Remove leading zeros from final result
	while ((*headR)->data == 0 && (*headR)->next != NULL)
	{
		dl_delete_first(headR, tailR);
	}

	return 0;
}