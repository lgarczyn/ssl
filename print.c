/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:01:03 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/10/10 19:39:23 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ssl.h"

static void	print_bytes(t_uchar *data, t_uint size)
{
	static char			hexa[16] = "0123456789abcdef";
	char				buf[128];
	t_uchar				c;
	t_uint				i;

	i = 0;
	while (i < sizeof(buf) - 1 && size > 0)
	{
		c = *data >> 4;
		buf[i++] = hexa[c];
		c = *data & 0xF;
		buf[i++] = hexa[c];
		size--;
		data++;
	}
	ft_putnstr(buf, i);
	if (size > 0)
		print_bytes(data, size);
}

static void	print_file(t_file *file)
{
	if (file->type == ty_stdin || file->type == ty_stdin_print)
		return ;
	if (file->type == ty_string)
		ft_putchar('"');
	ft_putstr(file->name);
	if (file->type == ty_string)
		ft_putchar('"');
}

static void	print_prologue(t_file *file, t_args *args)
{
	if (file->type == ty_stdin || file->type == ty_stdin_print)
		return ;
	ft_putstr(args->module->display_name);
	ft_putstr(" (");
	print_file(file);
	ft_putstr(") = ");
}

void		print_hash(t_uchar *data, t_uint size, t_file *file, t_args *args)
{
	if (!args->reversed && !args->quiet)
		print_prologue(file, args);
	print_bytes(data, size);
	if (args->reversed && !args->quiet)
	{
		ft_putstr(" ");
		print_file(file);
	}
	ft_putchar('\n');
}
