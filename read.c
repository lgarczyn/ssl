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

int				read_bufferized(t_file *file, t_uchar *buffer, t_uint size)
{
	int			r;
	t_uint		available;

	available = file->buffer_len - file->buffer_pos;
	r = MIN(size, available);
	if (r > 0)
	{
		ft_memcpy(buffer, file->buffer + file->buffer_pos, r);
		file->buffer_pos += r;
		return (r);
	}
	file->buffer_len = 0;
	file->buffer_pos = 0;
	r = 0;
	if (file->type != ty_string)
	{
		r = read(file->fd, file->buffer, BUFFER_SIZE);
		if (file->type == ty_stdin_print)
			write(STDOUT, file->buffer, r);
	}
	if (r < 0)
		return (r);
	file->buffer_len = r;
	file->buffer_pos = MIN(size, file->buffer_len);
	ft_memcpy(buffer, file->buffer, file->buffer_pos);
	return (file->buffer_pos);
}

/*
** Read 'size' character into buffer f, unless EOF is reached or err is raised
*/

int				read_safe(t_file *file, t_uchar *buffer, t_uint size)
{
	int			r;
	t_uint		read_full;

	if (file->status)
	{
		ft_bzero(buffer, size);
		return (0);
	}
	read_full = 0;
	while (read_full < size)
	{
		r = read_bufferized(file, buffer + read_full, size - read_full);
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
** Always fully fills the buffer according to spec
*/

bool			read_padded_32(t_file *file, t_uchar *buffer, t_endian endian)
{
	int 		r;
	bool		was_ok;

	if (file->padding_finished)
		return (false);
	was_ok = file->status == st_ok;
	r = read_safe(file, buffer, MD5_BLOCK);
	if (r < MD5_BLOCK)
	{
		if (was_ok)
		{
			buffer[r++] = 0x80;
		}
		if (r <= MD5_PAD)
		{
			*(t_usize*)&buffer[MD5_PAD] = WRITE64_E(file->size * 8, endian);
			file->padding_finished = true;
		}
	}
	return (true);
}


/*
** Read then pad file in MD5_SIZE blocks
** Always fully fills the buffer according to spec
*/

bool			read_padded_64(t_file *file, t_uchar *buffer, t_endian endian)
{
	int 		r;
	bool		was_ok;

	if (file->padding_finished)
		return (false);
	was_ok = file->status == st_ok;
	r = read_safe(file, buffer, SHA512_BLOCK);
	if (r < SHA512_BLOCK)
	{
		if (was_ok)
		{
			buffer[r++] = 0x80;
		}
		if (r <= SHA512_PAD)
		{
			*(t_usize*)&buffer[SHA512_PAD + 8] = WRITE64_E(file->size * 8, endian);
			file->padding_finished = true;
		}
	}
	return (true);
}

