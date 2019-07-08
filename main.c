/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:40:24 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/09 00:54:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static t_module		g_modules[] =
{
	{"md5", &module_md5},
	{"sha256", &module_sha256},
	{NULL, NULL}
};

int					main(int argc, char **argv)
{
	t_args			args;
	t_module		*m;

	if (argc < 1)
		return (format());
	args = get_args(argc, argv);
	if (args.err)
		return (ERR);
	m = g_modules;
	while (m->name)
	{
		if (ft_strcmp(m->name, args.module))
		{
			return (m->fn(&args));
		}
	}
	return (format());
}
