#include "shell.h"

/**
* _check_env - That function checks if
* the typed variable is an env variable
* @h: head of linked list
* @str: input string
* @mydata: data structure
* Return: no return
*/
void _check_env(r_var **h, char *str, data_shell *mydata)
{
int row, chr, x, lval;
char **_envro;

_envro = mydata->_environ;
for (row = 0; _envro[row]; row++)
{
for (x = 1, chr = 0; _envro[row][chr]; chr++)
{
if (_envro[row][chr] == '=')
{
lval = _strlen(_envro[row] + chr + 1);
add_rvar_node(h, x, _envro[row] + chr + 1, lval);
return;
}

if (str[x] == _envro[row][chr])
x++;
else
break;
}
}

for (x = 0; str[x]; x++)
{
if (str[x] == ' ' || str[x] == '\t' || str[x] == ';' || str[x] == '\n')
break;
}

add_rvar_node(h, x, NULL, 0);
}

/**
* check_vars -function that checks if the typed variable is $$ or $?
* @h: h of the linked list
* @str: input string
* @lsta: last status of the Shell
* @mydata: data structure
* Return: no return
*/
int check_vars(r_var **h, char *str, char *lsta, data_shell *mydata)
{
int n, lste , lpid;

lste  = _strlen(lsta);
lpid = _strlen(mydata->pid);

for (n = 0; str[n]; n++)
{
if (str[n] == '$')
{
if (str[n + 1] == '?')
add_rvar_node(h, 2, lsta, lste ), n++;
else if (str[n + 1] == '$')
add_rvar_node(h, 2, mydata->pid, lpid), n++;
else if (str[n + 1] == '\n')
add_rvar_node(h, 0, NULL, 0);
else if (str[n + 1] == '\0')
add_rvar_node(h, 0, NULL, 0);
else if (str[n + 1] == ' ')
add_rvar_node(h, 0, NULL, 0);
else if (str[n + 1] == '\t')
add_rvar_node(h, 0, NULL, 0);
else if (str[n + 1] == ';')
add_rvar_node(h, 0, NULL, 0);
else
_check_env(h, str + n, mydata);
}
}

return (n);
}

/**
* replaced_input - Function for replace string into variables
*
* @h: h of the linked list
* @str: input string
* @ni: new input string (replaced)
* @nl: new length
* Return: replaced string
*/
char *replaced_input(r_var **h, char *str, char *ni, int nl)
{
r_var *ind;
int n, x, k;

ind = *h;
for (x = n = 0; n < nl; n++)
{
if (str[x] == '$')
{
if (!(ind->len_var) && !(ind->len_val))
{
ni[n] = str[x];
x++;
}
else if (ind->len_var && !(ind->len_val))
{
for (k = 0; k < ind->len_var; k++)
x++;
n--;
}
else
{
for (k = 0; k < ind->len_val; k++)
{
ni[n] = ind->val[k];
n++;
}
x += (ind->len_var);
n--;
}
ind = ind->next;
}
else
{
ni[n] = str[x];
x++;
}
}

return (ni);
}

/**
* rep_var -that functio is for call a functions
* that replace string into vars.
* @str: input string
* @mydata: data structure
* Return: replaced string
*/
char *rep_var(char *str, data_shell *mydata)
{
r_var *h, *ind;
char *status, *ni;
int olen, nl;

status = aux_itoa(mydata->status);
h = NULL;

olen = check_vars(&h, str, status, mydata);

if (h == NULL)
{
free(status);
return (str);
}

ind = h;
nl = 0;

while (ind != NULL)
{
nl += (ind->len_val - ind->len_var);
ind = ind->next;
}

nl += olen;

ni = malloc(sizeof(char) * (nl + 1));
ni[nl] = '\0';

ni = replaced_input(&h, str, ni, nl);

free(str);
free(status);
free_rvar_list(&h);

return (ni);
}

