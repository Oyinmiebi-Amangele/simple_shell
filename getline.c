#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_siz: The size in bytes of the allocated space for ptr.
 * @new_siz: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_siz, unsigned int new_siz)
{
	void *memory;
	char *ptr_copy, *filter;
	unsigned int ind;

	if (new_siz == old_siz)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(new_siz);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_siz == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memory = malloc(sizeof(*ptr_copy) * new_siz);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filter = memory;

	for (ind = 0; ind < old_siz && ind < new_siz; ind++)
		filter[ind] = *ptr_copy++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buff: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buff, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		*lineptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}
/**
 * _getline - function to getline.
 * @lineptr: line pointer.
 * @n: size.
 * @stream: the file.
 * Return: int.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buff;
	int r = 0;

	if (input == 0)
		fflush(stream);
	else
		return (-1);

	input = 0;
	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buff = _realloc(buff, input, input + 1);
		buff[input] = c;
		input++;
	}
	buff[input] = '\0';
	assign_lineptr(lineptr, n, buff, input);
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

