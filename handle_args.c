#include "shell.h"

/**
 * handle_args - Read user input, parses it, and execute
 * the command with args.
 * @exe_ret: A pointer to an integer to store the exit status
 * of the executed command.
 *
 * Return: An integer representing the status of the shell.
 */
int handle_args(int *exe_ret)
{
	char buffer[BUFSIZE];
	char *args[MAX_ARGS];
	char *command;
	int argc = 0;
	int status, i;

	/*clear the buffer and args array*/
	_memset(buffer, 0, sizeof(buffer));
	for (i = 0; i < MAX_ARGS; i++)
	{
		args[i] = NULL;
	}

	/* Read user input*/
	if (read_user_input(buffer, BUFSIZE) == END_OF_FILE)
		return (END_OF_FILE);
	/* Tokenize user input into command and argumnets*/
	argc = tokenize_input(buffer, args, MAX_ARGS);
	if (argc == 0)
		return (0);
	command = args[0];
	/* Handle built-in commands*/
	if (_strcmp(command, "exit") == 0)
		return (EXIT);
	/* Execute the command with arguments */
	status = execute(args, environ);

	*exe_ret = status;
	return (status);
}

/**
 * read_user_input - Reads user input from stdin.
 * @buffer: A buffer to store the user input.
 * @size: The maximum size of the buffer.
 *
 * Return: The number of bytes read from stdin.
 */
int read_user_input(char *buffer, int size)
{
	int i, c;

	for (i = 0; i < size - 1; i++)
	{
		c = _getchar();
		if (c == EOF || c == '\n')
			break;
		buffer[i] = c;
	}
	buffer[i] = '\0';
	if (c == EOF)
		return (END_OF_FILE);
	return (i);
}

/**
 * tokenize_input - Tokenize the input string into an
 * array of arguments.
 * @input: The input string to be tokenized.
 * @args: An array to store the tokenized arguments.
 * @max_args: The maximum number of argumnets the
 * array can hold,
 *
 * Return: The number of arguments tokenized.
 */

int tokenize_input(char *input, char **args, int max_args)
{
	int argc = 0;
	char *token;

	token = strtok(input, " \t\n");
	while (token != NULL && argc < max_args - 1)
	{
		args[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	args[argc] = NULL;
	return (argc);
}

/**
 * _getchar - A custom implementation of getchar to read a
 * character from stdin.
 *
 * Return: The character read from stdin of EOF on error.
 */
int _getchar(void)
{
	char c;

	if (read(STDIN_FILENO, &c, 1) == 1)
		return (c);
	return (EOF);
}
