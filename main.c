/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:40:24 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/20 19:17:00 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include <stdio.h>
#include <unistd.h>


static t_module		g_modules[] =
{
	{"md5", "MD5", &module_md5},
	{"sha256", "SHA256", &module_sha256},
	{NULL, NULL, NULL}
};

t_args				get_args(int argc, char **argv)
{
	t_args			args;
	t_module		*m;

	args = (t_args){.path = argv[0], .argc = argc - 2, .argv = argv + 2};
	while (*args.argv)
	{
		if (ft_strcmp(*args.argv, "-q") == 0)
			args.quiet = true;
		else if (ft_strcmp(*args.argv, "-r") == 0)
			args.reversed = true;
		else if (ft_strcmp(*args.argv, "-p") == 0)
			args.print_stdin = true;
		else
			break;
		args.argc--;
		args.argv++;
	}
	m = g_modules;
	while (m->name)
	{
		if (ft_strcmp(m->name, argv[1]) == 0)
			args.module = m;
		m++;
	}
	return (args);
}

int					format(void)
{
	ft_putstr("usage: ft_ssl COMMAND [OPTION]... [-s STRING] [FILE]...\n");
	return (ERR);
}

static int			dispatch_hash(t_args *args, t_file *file)
{
	if (file->status == st_ok)
		args->module->fn(args, file);
	if (file->status == st_err)
	{
		ft_putstr(args->path);
		ft_putchar(' ');
		ft_putstr(args->module->name);
		ft_putstr(": ");
		ft_putstr(file->name);
		ft_putstr(": ");
		ft_putstr(strerror(file->err));
		ft_putchar('\n');			
	}
	close_file(file);
	return (file->status == st_err);
}

static int			dispatch(t_args *args)
{
	int				err;
	int				i;
	t_file			file;

	err = 0;
	if (args->argc == 0 || args->print_stdin)
	{
		file = open_stdin(args->print_stdin);
		err |= dispatch_hash(args, &file);
	}
	i = 0;
	while (i < args->argc)
	{
		if (ft_strcmp(args->argv[i], "-s") == 0 && i + 1 < args->argc)
			file = open_string(args->argv[++i]);
		else
			file = open_file(args->argv[i]);
		err |= dispatch_hash(args, &file);
		i++;
	}
	return (err);
}

int					main(int argc, char **argv)
{
	t_args			args;

	if (argc <= 1)
		return (format());
	args = get_args(argc, argv);
	if (args.err)
		return (ERR);
	if (args.module)
		return (dispatch(&args));
	ft_putstr(args.path);
	ft_putstr(": Error: '");
	ft_putstr(argv[1]);
	ft_putstr(
"' is an invalid command.\n\
Message Digest commands:\n\
\tmd5\n\
\tsha256\n");
	return (format());
}
