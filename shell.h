#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - the real struct that contains all relevant data on runtime
 * @av: an argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - The real single linked list
 * @len_var: a length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - The builtin struct for command args.
 * @name: name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *mydata);
} builtin_t;

/* mylist_0.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* mylist_1.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* mystring_0.c */
char *_strcat(char *des_str, const char *s);
char *_strcpy(char *des_str, char *s);
int _strcmp(char *str1, char *str2);
char *_strchr(char *str, char charac);
int _strspn(char *seg, char *acb);

/*mymemory.c*/

void _memcpy(void *desp, const void *sou_p, unsigned int size);
void *_realloc(void *p, unsigned int s_o, unsigned int new_s);
char **_reallocdp(char **p, unsigned int s_o, unsigned int new_s);

/* mystring_1.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int compa_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* mystring_2.c */
void rev_string(char *s);

/* myerror_4.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *mydata, char *input, int i, int bool);
int check_syntax_error(data_shell *mydata, char *input);

/* myshellloop.c */
char *delete_without_comment(char *str);
void do_shell_loop(data_shell *mydata);

/* myreadline.c */
char *myread_line(int *value);

/* mysplit.c */
char *my_swap_char(char *str, int swpty);
void my_add_nodes(sep_list **hs, line_list **hl, char *str);
void go_to_next(sep_list **list_s, line_list **ll, data_shell *mydata);
int split_commands(data_shell *mydata, char *str);
char **my_split_line(char *str);

/*myrepvar.c */
void _check_env(r_var **head, char *str, data_shell *mydata);
int _check_vars(r_var **head, char *str, char *lsta, data_shell *mydata);
char *replaced_input(r_var **head, char *str, char *ni, int nl);
char *rep_var(char *str, data_shell *mydata);



/* mygetline.c */
void bring_line(char **lineptr, size_t *o, char *buffer, size_t p);
ssize_t get_line(char **lineptr, size_t *o, FILE *stream);

/* myexecline */
int exec_line(data_shell *mydata);

/*my executor.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *mydata);
int check_error_cmd(char *dir, data_shell *mydata);
int cmd_exec(data_shell *mydata);

/* myenvi_0.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *mydata);

/* myenvi_1.c */
char *copy_info(char *ne, char *val);
void set_env(char *ne, char *val, data_shell *mydata);
int _setenv(data_shell *mydata);
int _unsetenv(data_shell *mydata);

/* mychangdir.c */
void cd_dot(data_shell *mydata);
void cd_to(data_shell *mydata);
void cd_previous(data_shell *mydata);
void cd_to_home(data_shell *mydata);

/* mycdshell.c */
int cd_shell(data_shell *mydatash);

/* mybuiltin.c */
int (*get_builtin(char *cmd))(data_shell *mydata);

/* myexitshell.c */
int exit_shell(data_shell *mydata);

/* mystdlib.c */
int get_len(int number);
char *aux_itoa(int number);
int _atoi(char *str);

/* myerror_0.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *mydata);
char *error_not_found(data_shell *mydata);
char *error_exit_shell(data_shell *mydata);

/* myerror_1.c */
char *error_get_alias(char **args);
char *error_env(data_shell *mydata);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *mydata);


/* myerror_2.c */
int get_error(data_shell *mydata, int eval);

/* mygetsigint.c */
void get_sigint(int sig);

/* myhelp_0.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* myhelp_1.c */
void help(void);
void help_alias(void);
void help_cd(void);

/* myhelp_2.c */
int get_help(data_shell *mydata);

#endif /*SHELL.H*/
