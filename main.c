/*
———————————————————————————————————————————————————————————————————————
Project: Arbitrary Precision Calculator (APC)
Author : Krishnakant Pore
Date   : 07/07/2025
Language: C

Description:
  This C program implements an arbitrary precision calculator that can perform
  basic arithmetic operations (+, -, *, /) on very large numbers that exceed
  the range of standard integer data types. Numbers are stored as doubly
  linked lists where each node contains a single digit.

File Info:
  - Uses doubly linked lists to store large numbers digit by digit
  - Supports addition, subtraction, multiplication, and division operations
  - Handles both positive and negative numbers with proper sign management
  - Removes leading zeros from results automatically

Sample User Inputs:
  ./a.out 12345678901234567890 + 98765432109876543210
    → Adds two large numbers and displays the result

  ./a.out -123456789 * 987654321
    → Multiplies two numbers with proper sign handling

  ./a.out 1000000000000000000 / 123456789
    → Divides large numbers and displays quotient
———————————————————————————————————————————————————————————————————————
*/

#include "apc.h"

int main(int argc, char *argv[])
{
	// Check if correct number of arguments provided
	if (argc != 4)
		printf("Invalid Input: Try again...\n");
	
	/* Declare the pointers */
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	char option, operator;

	do
	{
		/* Code for reading the inputs */
		char *str1 = argv[1];
		char *str2 = argv[3];
		int digi1;
		int digi2;
		int sign1 = 0; // 0 for positive, 1 for negative
		int sign2 = 0;

		/* Function for extracting the operator */
		operator = argv[2][0];

		// Fill the number 1 in the double linked list 1
		for (int i = 0; str1[i] != '\n' && str1[i] != '\0'; i++)
		{
			// Check for sign at the beginning
			if (str1[0] == '-')
				sign1 = 1;
			if (str1[0] == '+')
				sign1 = 0;

			// Convert character digit to integer and store in list
			if ('0' <= str1[i] && str1[i] <= '9')
			{
				digi1 = str1[i] - '0';
				dl_insert_last(&head1, &tail1, digi1);
			}
			else if (str1[i] == '-' || str1[i] == '+')
			{
				continue;
			}
			else
			{
				printf("Invalid Input: Try again...\n");
				return 0;
			}
		}

		// Fill the number 2 in the double linked list 2
		for (int i = 0; str2[i] != '\n' && str2[i] != '\0'; i++)
		{
			// Check for sign at the beginning
			if (str2[0] == '-')
				sign2 = 1;
			if (str2[0] == '+')
				sign2 = 0;

			// Convert character digit to integer and store in list
			if ('0' <= str2[i] && str2[i] <= '9')
			{
				digi2 = str2[i] - '0';
				dl_insert_last(&head2, &tail2, digi2);
			}
			else if (str2[i] == '-' || str2[i] == '+')
			{
				continue;
			}
			else
			{
				printf("Invalid Input: Try again...\n");
				return 0;
			}
		}

		// Skip leading zeros and signs for magnitude comparison
		while (*str1 && (*str1 < '1' || *str1 > '9'))
		{
			str1++;
		}
		while (*str2 && (*str2 < '1' || *str2 > '9'))
		{
			str2++;
		}

		switch (operator)
		{
		case '+':
			// Addition logic: same signs add, different signs subtract
			if (sign1 == sign2)
			{
				// Same signs: add magnitudes, preserve sign
				if (sign1)
					printf("-");
				addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			}
			else
			{
				// Different signs: subtract larger from smaller
				int cmp = (strlen(str1) != strlen(str2)) ? strlen(str1) - strlen(str2) : strcmp(str1, str2);
				if (cmp >= 0)
				{
					if (sign1)
						printf("-");
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
				}
				else
				{
					if (sign2)
						printf("-");
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
				}
			}
			print_list(headR);
			break;

		case '-':
			// Subtraction logic: handle sign combinations
			if (sign1 != sign2)
			{
				// Different signs: add magnitudes, use first operand's sign
				if (sign1)
					printf("-");
				addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			}
			else
			{
				// Same signs: subtract magnitudes
				int cmp = (strlen(str1) != strlen(str2)) ? strlen(str1) - strlen(str2) : strcmp(str1, str2);
				if (cmp >= 0)
				{
					if (sign1)
						printf("-");
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
				}
				else
				{
					if (!sign1)
						printf("-");
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
				}
			}
			print_list(headR);
			break;

		case '*':
			// Multiplication: result is negative if signs differ
			if (sign1 != sign2)
				printf("-");
			multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			print_list(headR);
			break;

		case '/':
			// Division: result is negative if signs differ
			if (sign1 != sign2)
				printf("-");
			division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			print_list(headR);
			break;

		default:
			printf("Invalid Input: Try again...\n");
		}
	} while (0);

	return 0;
}

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
	// Allocate memory for new node
	Dlist *new = malloc(sizeof(Dlist));

	if (new == NULL)
	{
		return FAILURE;
	}

	// Initialize new node data and pointers
	new->data = data;
	new->next = *head;
	new->prev = NULL;

	// Handle empty list case
	if (*head == NULL)
	{
		*tail = new;
		*head = new;
		return SUCCESS;
	}
	else
	{
		// Update existing head's previous pointer
		(*head)->prev = new;
		*head = new;
		return SUCCESS;
	}
}

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
	// Allocate memory for new node
	Dlist *new = malloc(sizeof(Dlist));

	if (new == NULL)
	{
		return FAILURE;
	}

	// Initialize new node data and pointers
	new->data = data;
	new->next = NULL;
	new->prev = *tail;

	// Handle empty list case
	if (*head == NULL)
	{
		*tail = new;
		*head = new;
		return SUCCESS;
	}
	else
	{
		// Update existing tail's next pointer
		(*tail)->next = new;
		*tail = new;
		return SUCCESS;
	}
}

void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		// printf("INFO : List is empty\n");
	}
	else
	{
		// Traverse and print each digit
		while (head)
		{
			/* Printing the list */
			printf("%d", head->data);

			/* Travering in forward direction */
			head = head->next;
		}
		printf("\n");
	}
}

int dl_delete_first(Dlist **head, Dlist **tail)
{
	// Check if list is empty
	if (*head == NULL)
	{
		return FAILURE;
	}
	else
	{
		// Handle single node case
		if (*head == *tail)
		{
			free(*head);
			*head = NULL;
			*tail = NULL;
			return SUCCESS;
		}
		else
		{
			// Move head to next node and free previous head
			*head = (*head)->next;
			free((*head)->prev);
			(*head)->prev = NULL;
			return SUCCESS;
		}
	}
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
	// Check if list is empty
	if (*head == NULL)
	{
		return FAILURE;
	}
	else
	{
		Dlist *temp;

		// Traverse and free each node
		while (*head != NULL)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp);
		}

		// Reset tail pointer
		*tail = NULL;
		return SUCCESS;
	}
}