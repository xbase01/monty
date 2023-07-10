#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * add_dnodeint_end - add a node to the tail of a doubly linked list
 *
 * @tail: pointer to the tail node
 * @num: integer data of the new node
 *
 * Return: address of the new node
 */
stack_t *add_dnodeint_end(stack_t **tail, const int num)
{
	stack_t *newnode;
	stack_t *current = *tail;

	newnode = malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		_exit(EXIT_FAILURE);
	}

	newnode->n = num;
	if (*tail == NULL)
	{
		*tail = global.opstack_head = newnode;
	}
	else
	{
		current->next = newnode;
		newnode->prev = current;
		global.opstack_tail = newnode;
	}

	return (newnode);
}

/**
 * add_dnodeint - add a node to beginning of a doubly linked list
 *
 * @head: address of the head node
 * @num: integer data of the new node
 *
 * Return: address of the new node
 *
 */
stack_t *add_dnodeint(stack_t **head, const int num)
{
	stack_t *newhead;

	newhead = malloc(sizeof(stack_t));
	if (newhead == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		_exit(EXIT_FAILURE);
	}
	newhead->n = num;

	newhead->next = *head;
	if (global.opstack_tail == NULL)
		global.opstack_tail = newhead;
	if (*head)
		(*head)->prev = newhead;
	*head = newhead;

	return (newhead);
}

/**
 * free_dlistint - free a doubly linked list
 *
 * @tail: the tail node
 *
 */
void free_dlistint(stack_t *tail)
{
	stack_t *temp;

	if (tail == NULL)
		return;
	while (tail)
	{
		temp = tail->prev;
		free(tail);
		tail = temp;
	}
}

