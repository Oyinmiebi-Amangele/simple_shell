#include "shell.h"

/**
 * _strncat - function that concatenates two strings given an integer n.
 * @src: source string.
 * @dest: destination string.
 * @n: integer.
 *
 * Return: returns dest.
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	int count = 0, count2 = 0;

	while (dest[count] != '\0')
	{
		count++;
	}

	while (count2 < n)
	{
		dest[count] = src[count2];
		if (src[count2] == '\0')
		{
			break;
		}
		count++;
		count2++;
	}
	return (dest);
}

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte, to the
 * buffer pointed to by dest.
 * @dest: destination.
 * @src: source.
 * Return: the pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	int count = 0;

	while (count >= 0)
	{
		*(dest + count) = *(src + count);
		if (*(src + count) == '\0')
			break;
		count++;
	}
	return (dest);
}
