#include "shell.h"

/**
* _memcpy - that function is for copies
* information between void pointers.
* @desp: destination pointer.
* @sou_p: source pointer.
* @size: size of the new pointer.
*
* Return: no return.
*/
void _memcpy(void *desp, const void *sou_p, unsigned int size)
{
char *char_ptr = (char *)sou_p;
char *char_newptr = (char *)desp;
unsigned int i;

for (i = 0; i < size; i++)
char_newptr[i] = char_ptr[i];
}

/**
* _realloc - That function reallocates a memory block.
* @p: pointer to the memory previously allocated.
* @s_o: size, in bytes, of the allocated space of ptr.
* @new_o: new size, in bytes, of the new memory block.
*Return: p.
* if new_o == s_o, returns ptr without changes.
* if malloc fails, returns NULL.
*/
void *_realloc(void *p, unsigned int s_o, unsigned int new_o)
{
void *newptr;

if (p == NULL)
return (malloc(new_o));

if (new_o == 0)
{
free(p);
return (NULL);
}

if (new_o == s_o)
return (p);

newptr = malloc(new_o);
if (newptr == NULL)
return (NULL);

if (new_o < s_o)
_memcpy(newptr, p, new_o);
else
_memcpy(newptr, p, s_o);

free(p);
return (newptr);
}

/**
* _reallocdp - That function reallocates
* a memory block of a double pointer.
* @p: double pointer to the memory previously allocated.
* @s_o: size, in bytes, of the allocated space of ptr.
* @new_o: new size, in bytes, of the new memory block.
* Return: p.
* if new_o == 0_s, returns ptr without changes.
* if malloc fails, returns NULL.
*/
char **_reallocdp(char **p, unsigned int s_o, unsigned int new_o)
{
char **newptr;
unsigned int i;

if (p == NULL)
return (malloc(sizeof(char *) * new_o));

if (new_o == s_o)
return (p);

newptr = malloc(sizeof(char *) * new_o);
if (newptr == NULL)
return (NULL);

for (i = 0; i < s_o; i++)
newptr[i] = p[i];

free(p);

return (newptr);
}
