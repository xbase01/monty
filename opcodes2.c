#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * add - add the top elements on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements, exit with a status
 * of EXIT_FAILURE. Result must be stored on the second top element, and
 * the top element must be removed
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack && (*stack)->prev)
	{
		temp = (*stack)->prev;
		(*stack)->prev->n += (*stack)->n;
		free(*stack);
		global.opstack_tail = temp;
	}
	else
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

/**
 * sub - subtract the top element from the second top element on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements, exit with a status
 * of EXIT_FAILURE. Result must be stored on the second top element, and
 * the top element must be removed
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack && (*stack)->prev)
	{
		temp = (*stack)->prev;
		(*stack)->prev->n -= (*stack)->n;
		free(*stack);
		global.opstack_tail = temp;
	}
	else
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

/**
 * divide - divide the second top element by the top element on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements, or the top element is 0
 * exit with a status of EXIT_FAILURE. Result must be stored on the second
 * top element, and the top element must be removed.
 */
void divide(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack && (*stack)->prev && (*stack)->n != 0)
	{
		temp = (*stack)->prev;
		(*stack)->prev->n /= (*stack)->n;
		free(*stack);
		global.opstack_tail = temp;
	}
	else
	{
		if (*stack == 0)
			fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		else if ((*stack)->n == 0)
			fprintf(stderr, "L%d: division by zero\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

/**
 * mul - multiply the top elements on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements, exit with a status
 * of EXIT_FAILURE. Result must be stored on the second top element, and
 * the top element must be removed
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack && (*stack)->prev)
	{
		temp = (*stack)->prev;
		(*stack)->prev->n *= (*stack)->n;
		free(*stack);
		global.opstack_tail = temp;
	}
	else
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

/**
 * mod - compute the remainder from the division of the second top element
 * by the top element on the stack
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * Description: if stack has less than 2 elements, or the top element is 0
 * exit with a status of EXIT_FAILURE. Result must be stored on the second
 * top element, and the top element must be removed.
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack && (*stack)->prev && (*stack)->n != 0)
	{
		temp = (*stack)->prev;
		(*stack)->prev->n %= (*stack)->n;
		free(*stack);
		global.opstack_tail = temp;
	}
	else
	{
		if (*stack == 0)
			fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		else if ((*stack)->n == 0)
			fprintf(stderr, "L%d: division by zero\n", line_number);
		_exit(EXIT_FAILURE);
	}
}

