#include "shell.h"

/**
* myread_line - That function is for read the input string.
*@value: return value of getline function
* Return: input string
*/
char *myread_line(int *value)
{
char *input = NULL;
size_t bufsize = 0;

*value = getline(&input, &bufsize, stdin);

return (input);
}
