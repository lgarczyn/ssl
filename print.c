/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:01:03 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/22 19:05:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ssl.h"

static void	print_uint(t_uint v, t_endian endian)
{
	char				buf[8];
	t_uchar				c;
	t_uint				i;

	if (endian == little_endian)
		v = swap32(v);
	i = 0;
	while (i < 8)
	{
		c = v >> (32 - 4);
		if (c < 10)
			buf[i] = '0' + c;
		else
			buf[i] = 'a' - 10 + c;
		i++;
		v <<= 4;
	}
	ft_putnstr(buf, sizeof(buf));
}

static void	print_file(t_file *file)
{
	if (file->type == ty_string)
		ft_putchar('"');
	ft_putstr(file->name);
	if (file->type == ty_string)
		ft_putchar('"');
}

static void print_prologue(t_file *file, t_args *args)
{	
	ft_putstr(args->module->display_name);
	ft_putstr(" (");
	print_file(file);
	ft_putstr(") = ");
}

void		print_hash(t_uint *vars, t_uint size, t_endian endian, t_file *file, t_args *args)
{
	t_uint	i;

	if (!args->reversed && !args->quiet)
		print_prologue(file, args);
	i = 0;
	while (i < size)
		print_uint(vars[i++], endian);
	if (args->reversed && !args->quiet)
	{
		ft_putstr(" ");
		print_file(file);
	}
	ft_putchar('\n');
}