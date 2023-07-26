#include "shell.h"

/**
 * create_error - Handles error cases and prints
 * error messages.
 * @args: An array of arguments that caused the error
 * @err: The error code to be returned.
 *
 * Return: The provided error code 'err'
 */

int create_error(char **args, int err)
{
	char *error_msgs[] = {
		"Permission denied",
		"Command not found"
	};

	if (err == 126 || err == 127)
	{
		char *command = args[0];
		char *error_msg = (err == 126) ? error_msgs[0] : error_msgs[1];

		write(STDERR_FILENO, args[0], _strlen(command));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		write(STDERR_FILENO, "\n", 1);
	}
	return (err);
}

/**
 * get_location - Find the location of the specified
 * command in the PATH.
 * @command: The command to find the location of.
 *
 * Return: A pointer to a string containing the full path
 * of the command or NULL if the command is not found
 * in the PATH.
 */

char *get_location(char *command)
{
	char *path = getenv("PATH");
	char *token, *directory;
	struct stat st;
	char *full_path;

	if (path == NULL)
		return (NULL);

	token = strtok(path, ":");
	while (token != NULL)
	{
		directory = token;
		token = strtok(NULL, ":");
		full_path = concat_paths(directory, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
		free(full_path);
	}

	return (NULL);
}

/**
 * concat_paths - Concatenate a directory and a command
 * to form a full path.
 * @directory: The directory part of the path.
 * @command: The command part of the path.
 *
 * Return: A pointer to a string containing the full path formed by
 * concatenating the directory and command.
 */
char *concat_paths(char *directory, char *command)
{
	int dir_len = _strlen(directory);
	int cmd_len = _strlen(command);
	char *full_path = malloc(dir_len + cmd_len + 2);

	if (full_path == NULL)
		return (NULL);
	_strcpy(full_path, directory);
	if (full_path[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		full_path[dir_len + 1] = '\0';
	}
	else
	{
		full_path[dir_len] = '\0';
	}
	_strcat(full_path, command);
	return (full_path);
}
