#include "shell.h"

#define MAX_DIGITS 11 /*Maximum number of digits for a 32-bit*/

/**
 * reverse_string - Reverses a given string in-place.
 * @str: The string to be reversed.
 * Return: Pointer to the revered string.
 */
char *reverse_string(char *str)
{
	int length = 0;
	char temp;

	while (str[length] != '\0')
		length++;
	for (int i = 0; i < length / 2; i++)
	{
		temp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = temp;
	}
	return (str);
}

/**
 * _itoa - Converts an integer to a string representation.
 * @num: The integer to be converted.
 * Return: Pointer to the string representation of the integer.
 */

char *_itoa(int num)
{
	static char buffer[MAX_DIGITS + 1];
	int is_negative = 0;
	int index = 0;

	if (num == 0)
	{
		buffer[index++] = '0';
		buffer[index] = '\0';
		return (buffer);
	}

	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}

	while (num > 0)
	{
		buffer[index++] = '0' + (num % 10);
		num /= 10;
	}
	if (is_negative)
		buffer[index++] = '-';
	buffer[index] = '\0';

	return (reverse_string(buffer));
}


/**
 * _strlen - function that gives us the length of a string.
 * @s: String character.
 *
 * Return: The count of the string.
 */
int _strlen(const char *s)
{
	int count = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		count++;
	}

	return (count);
}

/**
 * _strcat - function that joins two strings together.
 * @src: sorce string.
 * @dest: destination string.
 *
 * Return: returns the destination string.
 */

char *_strcat(char *dest, const char *src)
{
	int count = 0, count2 = 0;

	while (dest[count] != '\0')
	{
		count++;
	}

	while (count2 >= 0)
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
 * _strncmp - Compare two strings up to a specified maximum length
 * @s1: The first input string
 * @s2: The second input string
 * @n: The maximum number of characters to copare
 *
 * Return:
 * An integer less than, equal to, or greater than zero
 * if the first n characters of s1 are found, respectively,
 * to be less than, to match, or be greater than the first
 * an characters of s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		if (*s1 == '\0')
		{
			break;
		}

		s1++;
		s2++;
		n--;
	}

	return (0);
}
