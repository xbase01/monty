#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "monty.h"

global_t global = { NULL, NULL, NULL, NULL, NULL, STACK };

/**
 * main - Entry point to the monty interpreter
 *
 * @argc: argument count
 * @argv: array of character strings as arguments
 *
 * Return: exits with status of EXIT_SUCCESS, or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	int linecount = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	global.fp = fopen(argv[1], "r");
	if (global.fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &len, global.fp) != -1)
	{
		linecount++;
		global.opcode = strtok(line, " \n");
		if (global.opcode == NULL || global.opcode[0] == '#')
			continue;
		if (check_opcode(global.opcode) == 0)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", linecount, global.opcode);
			_exit(EXIT_FAILURE);
		}
		global.value = strtok(NULL, " \n");
		execute_opcode(global.opcode, &global.opstack_tail, linecount);
	}
	free_dlistint(global.opstack_tail);
	if (global.opcode)
		free(global.opcode);
	fclose(global.fp);

	exit(EXIT_SUCCESS);
}

/**
 * check_opcode - check whether an opcode is valid
 *
 * @input: the character string to check
 *
 * Return: 1 if it's a valid opcode, otherwise 0
 */
int check_opcode(char *input)
{
	int i;
	char *opcodes[] = {
		"push", "pall", "pint", "pop", "swap", "add", "nop",
		"sub", "div", "mul", "mod", "pchar", "pstr", "rotl",
		"rotr", "stack", "queue", NULL
	};

	for (i = 0; opcodes[i]; ++i)
		if (strcmp(opcodes[i], input) == 0)
			return (1);
	return (0);
}

/**
 * execute_opcode - execute an opcode
 *
 * @opcode: the opcode to execute
 * @stack: doubly linked list to operate on
 * @line_n: current line number
 *
 */
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_n)
{
	int i;
	instruction_t instructions[] = {
		{ "push", push },
		{ "pall", pall },
		{ "pint", pint },
		{ "pop", pop },
		{ "swap", swap },
		{ "add", add },
		{ "nop", nop },
		{ "sub", sub },
		{ "div", divide },
		{ "mul", mul },
		{ "mod", mod },
		{ "pchar", pchar },
		{ "pstr", pstr },
		{ "rotl", rotl },
		{ "rotr", rotr },
		{ "stack", stackf },
		{ "queue", queue },
		{ NULL, NULL }
	};

	for (i = 0; instructions[i].opcode; ++i)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_n);
			break;
		}
	}
}

/**
 * stackf - set the format of the data to a stack (LIFO)
 * this is the default behavior of the program
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * When switching mode:
 *   The top of the stack becomes the front of the queue
 *   The front of the queue becomes the top of the stack
 *
 */
void stackf(__attribute__((unused)) stack_t **stack,
		__attribute__((unused)) unsigned int line_number)
{
	global.mode = STACK;
}

/**
 * queue - set the format of the data to a queue (FIFO)
 *
 * @stack: pointer to the stack to manipulate
 * @line_number: current line number in the bytecode file
 *
 * When switching mode:
 *   The top of the stack becomes the front of the queue
 *   The front of the queue becomes the top of the stack
 *
 */
void queue(__attribute__((unused)) stack_t **stack,
		__attribute__((unused)) unsigned int line_number)
{
	global.mode = QUEUE;
}

