#include "shell.h"

/**
* strcat_cd - function that concatenates the message for cd _error
*
* @mydata: data relevant (directory)
* @sms: message to print
* @_error: output message
* @verstr: counter lines
* Return: _error message
*/
char *strcat_cd(data_shell *mydata, char *sms, char *_error, char *ver_str)
{
char *illigal_f;

_strcpy(_error, mydata->av[0]);
_strcat(_error, ": ");
_strcat(_error, ver_str);
_strcat(_error, ": ");
_strcat(_error, mydata->args[0]);
_strcat(_error, sms);
if (mydata->args[1][0] == '-')
{
illigal_f = malloc(3);
illigal_f[0] = '-';
illigal_f[1] = mydata->args[1][1];
illigal_f[2] = '\0';
_strcat(_error, illigal_f);
free(illigal_f);
}
else
{
_strcat(_error, mydata->args[1]);
}

_strcat(_error, "\n");
_strcat(_error, "\0");
return (_error);
}

/**
* error_get_cd - Function that shows an _error
* message for change directory command in get_cd
* @mydata: data relevant directory
* Return: Error message
*/
char *error_get_cd(data_shell *mydata)
{
int length, len_id;
char *_error, *ver_str, *sms;

ver_str = aux_itoa(mydata->counter);
if (mydata->args[1][0] == '-')
{
sms = ": Illegal option ";
len_id = 2;
}
else
{
sms = ": can't cd to ";
len_id = _strlen(mydata->args[1]);
}

length = _strlen(mydata->av[0]) + _strlen(mydata->args[0]);
length += _strlen(ver_str) + _strlen(sms) + len_id + 5;
_error = malloc(sizeof(char) * (length + 1));

if (_error == 0)
{
free(ver_str);
return (NULL);
}

_error = strcat_cd(mydata, sms, _error, ver_str);

free(ver_str);

return (_error);
}

/**
* error_not_found - function that generate _error
* message for command not found
* @mydata: data relevant (counter, arguments)
* Return: Error message
*/
char *error_not_found(data_shell *mydata)
{
int length;
char *_error;
char *ver_str;

ver_str = aux_itoa(mydata->counter);
length = _strlen(mydata->av[0]) + _strlen(ver_str);
length += _strlen(mydata->args[0]) + 16;
_error = malloc(sizeof(char) * (length + 1));
if (_error == 0)
{
free(_error);
free(ver_str);
return (NULL);
}
_strcpy(_error, mydata->av[0]);
_strcat(_error, ": ");
_strcat(_error, ver_str);
_strcat(_error, ": ");
_strcat(_error, mydata->args[0]);
_strcat(_error, ": not found\n");
_strcat(_error, "\0");
free(ver_str);
return (_error);
}

/**
* error_exit_shell - function that generates an
* _error message for exit in get_exit
* @mydata: data relevant (counter, arguments)
*
* Return: Error message
*/
char *error_exit_shell(data_shell *mydata)
{
int length;
char *_error;
char *ver_str;

ver_str = aux_itoa(mydata->counter);
length = _strlen(mydata->av[0]) + _strlen(ver_str);
length += _strlen(mydata->args[0]) + _strlen(mydata->args[1]) + 23;
_error = malloc(sizeof(char) * (length + 1));
if (_error == 0)
{
free(ver_str);
return (NULL);
}
_strcpy(_error, mydata->av[0]);
_strcat(_error, ": ");
_strcat(_error, ver_str);
_strcat(_error, ": ");
_strcat(_error, mydata->args[0]);
_strcat(_error, ": Illegal number: ");
_strcat(_error, mydata->args[1]);
_strcat(_error, "\n\0");
free(ver_str);

return (_error);
}
