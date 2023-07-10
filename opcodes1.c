#include <stdlib.h>
#include <stdio.h>
#include "monty.h"

/**
 * push - push an element onto the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if no argument specified or argument is not an integer
 * exit with a status of EXIT_FAILURE
 */
void push(stack_t **stack, unsigned int line_number)
{
	if (global.value == NULL || check_integer(global.value) == 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		_exit(EXIT_FAILURE);
	}
	if (global.mode == STACK)
		add_dnodeint_end(stack, atoi(global.value));
	else
		add_dnodeint(&global.opstack_head, atoi(global.value));
}

/**
 * pint - print the top element on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack is null exit with a status of EXIT_FAILURE
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		_exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pall - print all elements on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack is empty, print nothing
 */
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
}

/**
 * pop - remove the top element on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack is null exit with a status of EXIT_FAILURE
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		_exit(EXIT_FAILURE);
	}
	temp = (*stack)->prev;
	free(*stack);
	global.opstack_tail = temp;
}

/**
 * swap - swap the top elements on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements,
 * exit with a status of EXIT_FAILURE
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack && (*stack)->prev)
	{
		temp = (*stack)->n;
		(*stack)->n = (*stack)->prev->n;
		(*stack)->prev->n = temp;
	}
	else
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

