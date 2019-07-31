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
	{"md5", &module_md5},
	{"sha256", &module_sha256},
	{NULL, NULL}
};

int					format(void)
{
	ft_putstr("usage: ft_ssl COMMAND [OPTION]... [-s STRING] [FILE]...\n");
	return (1);
}

t_args				get_args(int argc, char **argv)
{
	t_args			args;

	args.path = argv[0];
	args.module = argv[1];
	args.argc = argc - 2;
	args.argv = argv + 2;
	args.err = 0;
	return (args);
}

int					dispatch(t_args *args, t_module *module)
{
	int				i;
	int				err;
	t_file			file;

	i = 0;
	err = 0;
	if (args->argc == 0)
	{
		file = open_stdin();
		module->fn(args, &file);
	}
	while (i < args->argc)
	{
		file = open_file(args->argv[i]);
		if (file.status == st_ok)
		{
			module->fn(args, &file);
			close(file.fd);
		}
		if (file.status == st_err)
		{
			printf("%s %s: %s: %s\n",
				args->path,
				args->module,
				args->argv[i],
				strerror(file.err));
		}
		i++;
	}
	return (err);
}

int					main(int argc, char **argv)
{
	t_args			args;
	t_module		*m;

	if (argc <= 1)
		return (format());
	args = get_args(argc, argv);
	if (args.err)
		return (ERR);
	m = g_modules;
	while (m->name)
	{
		if (ft_strcmp(m->name, args.module) == 0)
		{
			return (dispatch(&args, m));
		}
		m++;
	}
	printf("%s: Error: '%s' is an invalid command.\n\
Message Digest commands:\n\tmd5\n\tsha256\n",
		args.path,
		args.module);
	return (format());
}
