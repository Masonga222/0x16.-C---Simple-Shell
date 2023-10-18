#include "shell.h"

/**
* _strcat - Function that concatenatse two strings
* @des_str: char pointer the desination of the copied string
* @sp: const char pointer the source of string
* Return: the dest
*/
char *_strcat(char *des_str, const char *sp)
{
int x;
int y;

for (x = 0; des_str[x] != '\0'; x++)
;

for (y = 0; sp[y] != '\0'; y++)
{
des_str[x] = sp[y];
x++;
}

des_str[x] = '\0';
return (des_str);
}
/**
* *_strcpy - Function that Copies the string pointed to by source.
* @des_str: Type char pointer the dest of the copied str
* @sp: Type char pointer the source of str
* Return: the dest.
*/
char *_strcpy(char *des_str, char *sp)
{

size_t t;

for (t = 0; sp[t] != '\0'; t++)
{
des_str[t] = sp[t];
}
des_str[t] = '\0';

return (des_str);
}
/**
* _strcmp - Function that is for  compare two strings.
* @str_1: type string compared
* @str_2: type string compared
* Return: Always 0.
*/
int _strcmp(char *str_1, char *str_2)
{
int x;

for (x = 0; str_1[x] == str_2[x] && str_1[x]; x++)
;

if (str_1[x] > str_2[x])
return (1);
if (str_1[x] < str_2[x])
return (-1);
return (0);
}
/**
* _strchr -Function that is for locate a character in a string,
* @str: string.
* @charact: character.
* Return: the pointer to the first occurrence of the character c.
*/
char *_strchr(char *str, char charact)
{
unsigned int x = 0;

for (; *(str + x) != '\0'; x++)
if (*(str + x) == charact)
return (str + x);
if (*(str + x) == charact)
return (str + x);
return ('\0');
}
/**
* _strspn - Function that is for get the length of a prefix substring.
* @segme: initial segment.
* @accb: accepted bytes.
* Return: the number of accepted bytes.
*/
int _strspn(char *segme, char *accb)
{
int x, y, bool;

for (x = 0; *(segme + x) != '\0'; x++)
{
bool = 1;
for (y = 0; *(accb + y) != '\0'; y++)
{
if (*(segme + x) == *(accb + y))
{
bool = 0;
break;
}
}
if (bool == 1)
break;
}
return (x);
}
