#include "shell.h"

/**
* compa_env_name - Function that compares
* env variables names with the name passed.
* @m: name of the environment variable
* @y: name passed
*
* Return: 0 if are not equal. Another value if they are.
*/
int compa_env_name(const char *m, const char *y)
{
int i;

for (i = 0; m[i] != '='; i++)
{
if (m[i] != y[i])
{
return (0);
}
}

return (i + 1);
}

/**
* _getenv - get an environment variable
* @y: name of the environment variable
* @_environ: environment variable
*
* Return: value of the environment variable if is found.
* In other case, returns NULL.
*/
char *_getenv(const char *y, char **_environ)
{
char *ptr_env;
int i, mov;

/* Initialize ptr_env value */
ptr_env = NULL;
mov = 0;
/* Compare all environment variables */
/* environ is declared in the header file */
for (i = 0; _environ[i]; i++)
{
/* If name and env are equal */
mov = compa_env_name(_environ[i], y);
if (mov)
{
ptr_env = _environ[i];
break;
}
}

return (ptr_env + mov);
}

/**
* _env - prints the evironment variables
*
* @mydata: data relevant.
* Return: 1 on success.
*/
int _env(data_shell *mydata)
{
int i, l;

for (i = 0; mydata->_environ[i]; i++)
{

for (l = 0; mydata->_environ[i][l]; l++)
;

write(STDOUT_FILENO, mydata->_environ[i], l);
write(STDOUT_FILENO, "\n", 1);
}
mydata->status = 0;

return (1);
}
