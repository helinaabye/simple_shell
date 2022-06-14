#include "shell.h"

/**
 * main - puts argument operation results
 * @argc: argument count
 * @argv: argument array
 * Return: returns 0 if successful
 */


int main(int argc, char **argv)
{
	char *cmd;

	do {
		print_prompt1();

		cmd = read_cmd();

		if (!cmd)
			exit(EXIT_SUCCESS);

		if (cmd[0] == '\0' || str_cmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}

		if (str_cmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			break;
		}
		_printf(cmd);
	} while (1);
	exit(EXIT_SUCCESS);
}

/**
 * read_cmd - reads a string from the standard input
 * Return: returns a string
 */

char *read_cmd(void)
{
	char buf[1024], ptrlen = 0, *ptr = NULL,  *ptr2 = NULL;
	int buflen = 0;

	while (fgets(buf, 1024, stdin))
	{
		buflen = _strlen(buf);

		if (!ptr)
			ptr = malloc(buflen + 1);

		else
		{
			ptr2 = realloc(ptr, ptrlen + buflen + 1);
			if (ptr2)
				ptr = ptr2;
			else
			{
				free(ptr);
				ptr = NULL;
			}
		}

		if (!ptr)
		{
			_printf("error: failed to alloc buffer:\n");
			return (NULL);
		}

		_strcpy(ptr + ptrlen, buf);

		if (buf[buflen - 1] == '\n')
		{
			if (buflen == 1 || buf[buflen - 2] != '\\')
				return (ptr);
			ptr[ptrlen + buflen - 2] = '\0';
			buflen -= 2;
			print_prompt2();
		}
		ptrlen += buflen;
	}
	return (ptr);
}