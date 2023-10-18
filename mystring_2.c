#include "shell.h"

/**
* rev_string - That function reverses a string.
* @inpt_s: input string.
* Return: no return.
*/
void rev_string(char *inpt_s)
{
int cou = 0, x, y;
char *str, temp;

while (cou >= 0)
{
if (inpt_s[cou] == '\0')
break;
cou++;
}
str = inpt_s;

for (x = 0; x < (cou - 1); x++)
{
for (y = x + 1; y > 0; y--)
{
temp = *(str + y);
*(str + y) = *(str + (y - 1));
*(str + (y - 1)) = temp;
}
}
}
