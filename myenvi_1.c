#include "shell.h"

/**
* copy_info - That function is for  copy
* informatio to create x new env or alias
* @ne: name (env or alias)
* @val: value (env or alias)
*
* Return: new env or alias.
*/
char *copy_info(char *ne, char *val)
{
char *new;
int len_name, len_value, len;

len_name = _strlen(ne);
len_value = _strlen(val);
len = len_name + len_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, ne);
_strcat(new, "=");
_strcat(new, val);
_strcat(new, "\0");

return (new);
}

/**
* set_env - That function sets an environment variable.
* @ne: name of the environment variable
* @val: value of the environment variable
* @mydata: data structure (environ)
* Return: no return
*/
void set_env(char *ne, char *val, data_shell *mydata)
{
int i;
char *var_env, *name_env;

for (i = 0; mydata->_environ[i]; i++)
{
var_env = _strdup(mydata->_environ[i]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, ne) == 0)
{
free(mydata->_environ[i]);
mydata->_environ[i] = copy_info(name_env, val);
free(var_env);
return;
}
free(var_env);
}

mydata->_environ = _reallocdp(mydata->_environ, i, sizeof(char *) * (i + 2));
mydata->_environ[i] = copy_info(ne, val);
mydata->_environ[i + 1] = NULL;
}

/**
* _setenv - That function  is for compare
* env variables names with the name passed.
* @mydata: data relevant (env name and env value)
*
* Return: 1 on success.
*/
int _setenv(data_shell *mydata)
{

if (mydata->args[1] == NULL || mydata->args[2] == NULL)
{
get_error(mydata, -1);
return (1);
}

set_env(mydata->args[1], mydata->args[2], mydata);

return (1);
}

/**
* _unsetenv - That function  for delete
* environment variable
*
* @mydata: data relevant envname
*
* Return: 1 on success.
*/
int _unsetenv(data_shell *mydata)
{
char **realloc_environ;
char *var_env, *name_env;
int x, y, z;

if (mydata->args[1] == NULL)
{
get_error(mydata, -1);
return (1);
}
z = -1;
for (x = 0; mydata->_environ[x]; x++)
{
var_env = _strdup(mydata->_environ[x]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, mydata->args[1]) == 0)
{
z = x;
}
free(var_env);
}
if (z == -1)
{
get_error(mydata, -1);
return (1);
}
realloc_environ = malloc(sizeof(char *) * (x));
for (x = y = 0; mydata->_environ[x]; x++)
{
if (x != z)
{
realloc_environ[y] = mydata->_environ[x];
y++;
}
}
realloc_environ[y] = NULL;
free(mydata->_environ[z]);
free(mydata->_environ);
mydata->_environ = realloc_environ;
return (1);
}
