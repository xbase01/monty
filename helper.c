#include <ctype.h>
#include "monty.h"

/**
 * check_integer - check whether a string is an integer
 *
 * @input: string to check
 *
 * Return: 1 if it's an integer, otherwise 0
 */
int check_integer(char *input)
{
	int i = 0;

	if (input[i] == '-')
	{
		i++;
		if (input[i] == 0)
			return (0);
	}
	for (; input[i]; ++i)
		if (isdigit(input[i]) == 0)
			return (0);
	return (1);
}

