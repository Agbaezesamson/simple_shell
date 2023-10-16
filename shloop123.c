#include "shell.h"

/**
 * hsh - Main shell loop
 * @info: Struct containing shell information
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_result = 0;

	while (read_status != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->error_number == -1)
			exit(info->status);
		exit(info->error_number);
	}
	return (builtin_result);
}

/**
 * find_builtin - Finds a built-in command
 * @info: Struct containing shell information
 *
 * Return: -1 if built-in not found,
 * 0 if built-in executed successfully,
 * 1 if built-in found but not successful,
 * 2 if built-in signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->arguments[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[i].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * find_command - Finds a command in PATH
 * @info: Struct containing shell information
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *cmd_path = NULL;
	int i, arg_count = 0;

	info->command_path = info->arguments[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0; info->arguments[i]; i++)
		if (!is_delimiter(info->arguments[i], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	cmd_path = find_command_path(info, _get_environment_variable(info, "PATH="),
			info->arguments[0]);
	if (cmd_path)
	{
		info->command_path = cmd_path;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || _get_environment_variable(info, "PATH=")
					|| info->arguments[0][0] == '/') && is_command(info, info->arguments[0]))
			fork_command(info);
		else if (*(info->input) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - Forks an exec thread to run a command
 * @info: Struct containing shell information
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->command_path, info->arguments, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
