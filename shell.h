#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

/**
 * struct info - Struct for the program's data
 * @program_name: The name of the executable
 * @input_line: Pointer to the input read for _getline
 * @command_name: Pointer to the first command typed by the user
 * @exec_counter: Number of executed commands
 * @file_descriptor: File descriptor to the input of commands
 * @tokens: Pointer to array of tokenized input
 * @env: Copy of the environ
 * @alias_list: Array of pointers with aliases.
 */
typedef struct info
{
char *program_name;
char *input_line;
char *command_name;
int exec_counter;
int file_descriptor;
char **tokens;
char **env;
char **alias_list;
} data_of_program;

/**
 * struct builtins - Struct for the builtins
 * @builtin: The name of the builtin
 * @function: The associated function to be called for each builtin
 */
typedef struct builtins
{
char *builtin;
int (*function)(data_of_program *data);
} builtins;


void initialize_data(data_of_program *data, int argc, char *argv[], char **env);
void sisifo(char *prompt, data_of_program *data);
void handle_ctrl_c(int opr UNUSED);


int read_command_line(data_of_program *data);
int split_logical_operators(char *array_commands[], int i, char array_operators[]);


void expand_variables(data_of_program *data);
void expand_alias(data_of_program *data);
int buffer_add(char *buffer, char *str_to_add);


void split_string(data_of_program *data);
char *_strtok(char *line, char *delim);


int execute_var(data_of_program *data);


int builtins_list(data_of_program *data);


char **tokenize_path(data_of_program *data);
int find_program(data_of_program *data);


void free_array_of_pointers(char **directories);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);


int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);


int execute_builtin_env(data_of_program *data);
int execute_builtin_set_env(data_of_program *data);
int execute_builtin_unset_env(data_of_program *data);

char *get_environment_value(char *name, data_of_program *data);
int set_env_key(char *key, char *value, data_of_program *data);
int remove_env_key(char *key, data_of_program *data);
void printEnv(data_of_program *data);

int write_to_stdout(char *string);
int write_to_stderr(char *string);
int print_error(int errorcode, data_of_program *data);

int string_length(char *string);
char *string_duplicate(char *string);
int string_compare(char *string1, char *string2, int number);
char *string_concatenate(char *string1, char *string2);
void string_reverse(char *string);

void convert_long_to_string(long number, char *string, int base);
int convert_str_to_int(char *a);
int count_characters(char *string, char *character);

int print_alias(data_of_program *data, char *alias);
char *get_alias(data_of_program *data, char *alias);
int set_alias(char *alias_string, data_of_program *data);

#endif /* SHELL_H */
