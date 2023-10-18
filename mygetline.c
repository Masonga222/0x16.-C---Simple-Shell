#include "shell.h"

/**
* bring_line -That function  assigns the line var for get_line
* @lineptr:is a Buffer that store the input string
* @buffer: string that is been called to line
* @o: size of line
* @p: size of buffer
*/
void bring_line(char **lineptr, size_t *o, char *buffer, size_t p)
{

if (*lineptr == NULL)
{
if  (p > BUFSIZE)
*o = p;

else
*o = BUFSIZE;
*lineptr = buffer;
}
else if (*o < p)
{
if (p > BUFSIZE)
*o = p;
else
*o = BUFSIZE;
*lineptr = buffer;
}
else
{
_strcpy(*lineptr, buffer);
free(buffer);
}
}
/**
* get_line - That function is for read inpt from stream
* @lineptr: is a buffer that stores the input str
* @o: size of lineptr
* @stream: stream to read from
* Return: The no of bytes
*/
ssize_t get_line(char **lineptr, size_t *o, FILE *stream)
{
int j;
static ssize_t input;
ssize_t retval;
char *buffer;
char x = 'z';

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * BUFSIZE);
if (buffer == 0)
return (-1);
while (x != '\n')
{
j = read(STDIN_FILENO, &x, 1);
if (j == -1 || (j == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (j == 0 && input != 0)
{
input++;
break;
}
if (input >= BUFSIZE)
buffer = _realloc(buffer, input, input + 1);
buffer[input] = x;
input++;
}
buffer[input] = '\n';
bring_line(lineptr, o, buffer, input);
retval = input;
if (j != 0)
input = 0;
return (retval);
}
