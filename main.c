#include "shell.h"

/**
 * sig_handler - Prints a new prompt upon a signal.
 *@sig: The signal.
 */

void sig_handler(int sig)
{
	char *new_prompt = "\nwatts $";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}


/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn, hist;
	int *exe_ret = &retn;
	char *prompt = "watts $ ", *new_line = "\n";

	char *name = argv[0];
	hist = 1;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	(void)argc;
	if (!environ)
		exit(-100);

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret);
		free_env();
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();

			exit(*exe_ret);
		}
	}

	free_env();

	return (*exe_ret);
}
