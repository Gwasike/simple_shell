#include "shell.h"

/**
 * _myend - ends the shell
 * @info: maintain constant function
 *
 * Return: Always 0
 */
int _myend(info_t *info)
{
	int endcheck;

	if (info->argv[1]) /* If there is an end arguement */
	{
		endcheck = _erratoi(info->argv[1]);
		if (endcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
	{
		endcheck = _erratoi(info->argv[1]);
		if (endcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @desc: maintain constant function
 *
 * Return: Always 0
 */
int _mycd(desc_t *desc)
{
	char *s, *dir, buff[1024];
	int chdir_ret;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!desc->argv[1])
	{
		dir = _getenv(desc, "HOME=");
		if (!dir)
			chdir_ret = /*TODO: what should this be? */
				chdir((dir = _getenv(desc, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(desc->argv[1], "-") == 0)
	{
		if (!_getenv(desc, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(desc, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(desc, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(desc->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(desc, "can't cd to ");
	{
		print_error(desc, "can't cd to ");
		_eputs(desc->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(desc, "OLDPWD", _getenv(desc, "PWD="));
		_setenv(desc, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myaid - changes the current directory
 * @desc: maintain constant function
 *
 * Return: Always 0
 */
int _myaid(desc_t *desc)
{
	char **arg_array;

	arg_array = desc->aegv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* node att_unused workaround */
	return (0);
}
