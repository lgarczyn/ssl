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
	ft_putstr("./ssl {md5,sha256} [files ... ]\n");
	return (1);
}

t_args				get_args(int argc, char **argv)
{
	t_args			args;

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
			printf("err %s %s %i\n", args->module, args->argv[i], file.err);
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
	return (format());
}
