#include "shell.h"

/**
 * main - Initialize the variables.
 * @argc: number of values received from the command line.
 * @argv: values received from the command line.
 * @env: number of values received from the command line.
 * Return: Always0
 */
int main(int argc, char *argv[], char *env[])
{
data_of_program data_struct = {NULL}, *data = &data_struct;
char *prompt = "";

initialize_data(data, argc, argv, env);

signal(SIGINT, handle_ctrl_c);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{
errno = 2;
prompt = PROMPT_MSG;
}
errno = 0;
sisifo(prompt, data);
return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
write_to_stdout("\n");
write_to_stdout(PROMPT_MSG);
}

/**
 * initialize_data - initialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments passed to the program execution
 * @env: environ passed to the program execution
 * @argc: number of values received from the command line
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
int k = 0;

data->program_name = argv[0];
data->input_line = NULL;
data->command_name = NULL;
data->exec_counter = 0;

if (argc == 1)
{
data->file_descriptor = STDIN_FILENO;
}
else
{
data->file_descriptor = open(argv[1], O_RDONLY);
if (data->file_descriptor == -1)
{
write_to_stderr(data->program_name);
write_to_stderr(": 0: Can't open ");
write_to_stderr(argv[1]);
write_to_stderr("\n");
exit(127);
}
}
data->tokens = NULL;
data->env = malloc(sizeof(char *) * 50);
if (env)
{
for (; env[k]; k++)
{
data->env[k] = string_duplicate(env[k]);
}
}
data->env[k] = NULL;
env = data->env;

data->alias_list = malloc(sizeof(char *) * 20);
for (k = 0; k < 20; k++)
{
data->alias_list[k] = NULL;
}
}

/**
 * sisifo - an infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: an infinite loop
 */
void sisifo(char *prompt, data_of_program *data)
{
int error_code = 0, string_len = 0;

while (++(data->exec_counter))
{
write_to_stdout(prompt);
error_code = string_len = read_command_line(data);

if (error_code == EOF)
{
free_all_data(data);
exit(errno); /* if EOF is the first Char of string, exit */
}
if (string_len >= 1)
{
expand_alias(data);
expand_variables(data);
split_string(data);
if (data->tokens[0])
{
error_code = execute_var(data);
if (error_code != 0)
{
print_error(error_code, data);
}
}
free_recurrent_data(data);
}
}
}
