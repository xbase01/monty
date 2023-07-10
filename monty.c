#ifndef _MONTY_H_
#define _MONTY_H_

#include <stdio.h>

#define STACK 1
#define QUEUE 0

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct global_s - structure to hold variables to be used across
 * multiple files
 *
 * @opcode: the operation code
 * @value: argument supplied to opcode
 * @fp: the bytecode file to interpret
 * @opstack_tail: tail node of the doubly linked list
 * @opstack_head: head node of the doubly linked list
 * @mode: mode of the program (either STACK or QUEUE)
 *
 */
typedef struct global_s
{
	char *opcode;
	char *value;
	FILE *fp;
	stack_t *opstack_tail;
	stack_t *opstack_head;
	int mode;
} global_t;

extern global_t global;

int check_opcode(char *input);
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_n);
void push(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void divide(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);
void pstr(stack_t **stack, unsigned int line_number);
void rotl(stack_t **stack, unsigned int line_number);
void rotr(stack_t **stack, unsigned int line_number);
void stackf(stack_t **stack, unsigned int line_number);
void queue(stack_t **stack, unsigned int line_number);
stack_t *add_dnodeint_end(stack_t **tail, const int num);
stack_t *add_dnodeint(stack_t **head, const int num);
void free_dlistint(stack_t *head);
int check_integer(char *input);
void _exit(int status);

#endif

