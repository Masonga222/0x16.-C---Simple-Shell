#include "shell.h"

/**
* exit_shell -Function that exits the shell
* @mydata: data relevant status and args
* Return: 0 on success.
*/
int exit_shell(data_shell *mydata)
{
unsigned int astat;
int is_digit;
int str_len;
int bignumber;

if (mydata->args[1] != NULL)
{
astat = _atoi(mydata->args[1]);
is_digit = _isdigit(mydata->args[1]);
str_len = _strlen(mydata->args[1]);
bignumber = astat > (unsigned int)INT_MAX;
if (!is_digit || str_len > 10 || bignumber)
{
get_error(mydata, 2);
mydata->status = 2;
return (1);
}
mydata->status = (astat % 256);
}
return (0);
}
