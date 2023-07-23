#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;

/**
 * struct list_s - New struct type for defining a linked list
 * @dir: A directory path.
 * @next: A pointer to another struct list_s
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;



/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_siz, unsigned int new_siz);
void assign_lineptr(char **lineptr, size_t *n, char *buff, size_t s);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
int execute_command(char *command, char **args);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_126(char **args);
char *error_127(char **args);

#endif /* _SHELL_H_ */

