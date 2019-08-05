/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:01:03 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/22 19:05:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "ssl.h"

t_file			open_file(char *name)
{
	t_file		file;

	ft_bzero(&file, sizeof(file));
	file.name = name;
	file.fd = open(name, O_RDONLY);
	file.status = file.fd < 0 ? st_err : st_ok;
	file.err = file.status == st_err ? errno : 0;
	file.type = ty_file;
	file.buffer = malloc(BUFFER_SIZE);
	return (file);
}

t_file			open_stdin(bool print_stdin)
{
	t_file		file;

	ft_bzero(&file, sizeof(file));
	file.name = "-";
	file.buffer = malloc(BUFFER_SIZE);
	file.type = print_stdin ? ty_stdin_print : ty_stdin;
	return (file);
}

t_file			open_string(char *data)
{
	t_file		file;

	ft_bzero(&file, sizeof(file));
	file.name = data;
	file.buffer = (t_uchar*)data;
	file.buffer_len = ft_strlen(data);
	file.type = ty_string;
	return (file);
}

void			close_file(t_file *file)
{
	if (file->type == ty_file)
		close(file->fd);
	if (file->type != ty_string)
		free(file->buffer);
}

void			add_size(t_file *file, t_uint add)
{
	file->size_lo += add;
	if (file->size_lo < add)
		file->size_hi++;
}