/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:01:03 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/10 04:31:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ssl.h"
#include "errno.h"

t_file			open_file(char *name)
{
	t_file		file;

	file.fd = open(name, O_RDONLY);
	file.status = file.fd < 0 ? st_err : st_ok;
	file.err = file.status == st_err ? errno : 0;
	file.size = 0;
	return (file);
}

/*
** Read 'size' character into buffer f, unless EOF is reached or err is raised
*/

int				read_safe(t_file *file, char *buffer, int size)
{
	int			r;
	int			read_full;

	if (file->status)
	{
		ft_bzero(buffer, size);
		return (0);
	}
	read_full = 0;
	while (read_full < size)
	{
		r = read(file->fd, buffer + read_full, size - read_full);
		if (r <= 0)
		{
			ft_bzero(buffer + read_full, size - read_full);
			file->status = r < 0 ? st_err : st_eof;
			file->err = file->status == st_err ? errno : 0;
			file->size += read_full;
			return (read_full);
		}
		read_full += r;
	}
	file->size += read_full;
	return (read_full);
}

/*
** Read then pad file in MD5_SIZE blocks
*/

bool			read_md5(t_file *file, char *buffer)
{
	int 		r;

	r = read_safe(file, buffer, MD5_BLOCK);
	if (r < MD5_BLOCK)
	{
		buffer[r++] = 0x80;
		if (r <= MD5_PAD)
		{
			buffer[MD5_PAD + 0] = file->size;
			buffer[MD5_PAD + 1] = file->size >> 8;
			buffer[MD5_PAD + 2] = file->size >> 16;
			buffer[MD5_PAD + 3] = file->size >> 24;
			buffer[MD5_PAD + 4] = file->size >> 32;
			buffer[MD5_PAD + 5] = file->size >> 40;
			buffer[MD5_PAD + 6] = file->size >> 48;
			buffer[MD5_PAD + 7] = file->size >> 56;
			return (false);
		}
	}
	return (true);
}

