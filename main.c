#include "shell.h"

/**
 * freedata - Function that frees data structure
 * @mydata: data structure
 * Return: no return
 */
void freedata(data_shell *mydata)
{
	unsigned int n;

	for (n = 0; mydata->_environ[n]; n++)
	{
		free(mydata->_environ[n]);
	}

	free(mydata->_environ);
	free(mydata->pid);
}

/**
 * _set_data - This function is for Initialize data struct
 *@mydata: data struct
 * @av: vector argument
 * Return: no return
 */
void _set_data(data_shell *mydata, char **av)
{
	unsigned int n;

	mydata->av = av;
	mydata->input = NULL;
	mydata->args = NULL;
	mydata->status = 0;
	mydata->counter = 1;

	for (n = 0; environ[n]; n++)
		;

	mydata->_environ = malloc(sizeof(char *) * (n + 1));

	for (n = 0; environ[n]; n++)
	{
		mydata->_environ[n] = _strdup(environ[n]);
	}

	mydata->_environ[n] = NULL;
	mydata->pid = aux_itoa(getpid());
}

/**
 * main - Function that entry point
 *@a_c: argument count
 * @av: argument vector
 * Return: 0 on success.
 */
int main(int a_c, char **av)
{
	data_shell mydata;
	(void) a_c;

	signal(SIGINT, get_sigint);
	_set_data(&mydata, av);
	do_shell_loop(&mydata);
	freedata(&mydata);
	if (mydata.status < 0)
		return (255);
	return (mydata.status);
}
