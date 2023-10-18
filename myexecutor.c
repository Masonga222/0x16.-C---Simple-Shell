#include "shell.h"

/**
* is_cdir - That function checks ":"
* if is in the current directory.
* @p: type char pointer char.
* @index: type int pointer of index.
* Return: 1 if the path is searchable in the cd, 0 otherwise.
*/
int is_cdir(char *p, int *index)
{
if (p[*index] == ':')
return (1);

while (p[*index] != ':' && p[*index])
{
*index += 1;
}

if (p[*index])
*index += 1;

return (0);
}

/**
* _which - Function that locates a command
* @cmd: command name
* @_environ: environment variable
* Return: location of the command.
*/
char *_which(char *cmd, char **_environ)
{
char *p, *ptr_path, *token_path, *dire;
int len_dir, len_cmd, i;
struct stat st;

p = _getenv("PATH", _environ);
if (p)
{
ptr_path = _strdup(p);
len_cmd = _strlen(cmd);
token_path = _strtok(ptr_path, ":");
i = 0;
while (token_path != NULL)
{
if (is_cdir(p, &i))
if (stat(cmd, &st) == 0)
return (cmd);
len_dir = _strlen(token_path);
dire = malloc(len_dir + len_cmd + 2);
_strcpy(dire, token_path);
_strcat(dire, "/");
_strcat(dire, cmd);
_strcat(dire, "\0");
if (stat(dire, &st) == 0)
{
free(ptr_path);
return (dire);
}
free(dire);
token_path = _strtok(NULL, ":");
}
free(ptr_path);
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}
if (cmd[0] == '/')
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}

/**
*is_executable - Function that determinesi
* f is an executable.
* @mydata: data structure
* Return: 0 if is not an executable, other number if it does
*/
int is_executable(data_shell *mydata)
{
struct stat st;
int x;
char *input;

input = mydata->args[0];
for (x = 0; input[x]; x++)
{
if (input[x] == '.')
{
if (input[x + 1] == '.')
return (0);
if (input[x + 1] == '/')
continue;
else
break;
}
else if (input[x] == '/' && x != 0)
{
if (input[x + 1] == '.')
continue;
x++;
break;
}
else
break;
}
if (x == 0)
return (0);

if (stat(input + x, &st) == 0)
{
return (x);
}
get_error(mydata, 127);
return (-1);
}

/**
* _check_error_cmd - function that verifies
* if user has permissions to access
* @destd: destination directory
* @mydata: data structure
* Return: 1 if there is an error, 0 if not
*/
int _check_error_cmd(char *destd, data_shell *mydata)
{
if (destd == NULL)
{
get_error(mydata, 127);
return (1);
}

if (_strcmp(mydata->args[0], destd) != 0)
{
if (access(destd, X_OK) == -1)
{
get_error(mydata, 126);
free(destd);
return (1);
}
free(destd);
}
else
{
if (access(mydata->args[0], X_OK) == -1)
{
get_error(mydata, 126);
return (1);
}
}

return (0);
}

/**
* cmd_exec -Function for executes command lines
* @mydata: data relevant (args and input)
* Return: 1 on success.
*/
int cmd_exec(data_shell *mydata)
{
pid_t pid;
pid_t wpid;
int state;
int execut;
char *dire;
(void) wpid;

execut = is_executable(mydata);
if (execut == -1)
return (1);
if (execut == 0)
{
dire = _which(mydata->args[0], mydata->_environ);
if (_check_error_cmd(dire, mydata) == 1)
return (1);
}

pid = fork();
if (pid == 0)
{
if (execut == 0)
dire = _which(mydata->args[0], mydata->_environ);
else
dire = mydata->args[0];
execve(dire + execut, mydata->args, mydata->_environ);
}
else if (pid < 0)
{
perror(mydata->av[0]);
return (1);
}
else
{
do {
wpid = waitpid(pid, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}

mydata->status = state / 256;
return (1);
}
