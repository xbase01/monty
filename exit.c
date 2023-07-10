#include <stdlib.h>
#include "monty.h"

/**
 * _exit - exit the interpreter
 *
 * @status: integer value to exit with
 *
 * Description: free malloced memory and exit with status
 */
void _exit(int status)
{
	free_dlistint(global.opstack_tail);
	if (global.opcode)
		free(global.opcode);
	fclose(global.fp);
	exit(status);
}

