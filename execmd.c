#include "shell.h"

/**
 * execute_command - Executes the given command with arguments.
 * @command: The command to be executed.
 * @args: An array of arguments to pass to the command.
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char *command, char **args)
{
	int status, ret = 0;
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error child:");
		return (1);
	}

	if (child_pid == 0)
	{
		execve(command, args, environ);
		if (errno == EACCES)
			ret = create_error(args, 126);
		free_env();
		_exit(ret);
	}
	else
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}

	return (ret);
}

/**
 * execute - Executes a command with arguments
 * and handles error cases.
 * @args: An array of arguments to pass to the command.
 * @front: An array of strings representing environment
 * variables (unused).
 *
 * Return: The exit status of the executed command
 * or an error code.
 */

int execute(char **args, char **front)
{
	int flag = 0, ret = 0;
	char *command = args[0];
	(void)front;

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || access(command, F_OK) == -1)
	{
		if (errno == EACCES)
			ret = create_error(args, 126);
		else
			ret = create_error(args, 127);
	}
	else
	{
		ret = execute_command(command, args);
	}

	if (flag)
		free(command);

	return (ret);
}
