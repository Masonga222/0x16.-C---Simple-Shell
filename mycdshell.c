#include "shell.h"

/**
* cd_shell - Function that changes current directory
* @mydata: data relevant
* Return: 1 on success
*/
int cd_shell(data_shell *mydata)
{
char *dir;
int isho, isho2, is_ddash;

dir = mydata->args[1];

if (dir != NULL)
{
isho = _strcmp("$HOME", dir);
isho2 = _strcmp("~", dir);
is_ddash = _strcmp("--", dir);
}

if (dir == NULL || !isho || !isho2 || !is_ddash)
{
cd_to_home(mydata);
return (1);
}

if (_strcmp("-", dir) == 0)
{
cd_previous(mydata);
return (1);
}

if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
{
cd_dot(mydata);
return (1);
}

cd_to(mydata);

return (1);
}
