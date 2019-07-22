/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:40:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/22 19:06:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SSL_H
# define __SSL_H

# include <stdbool.h>
# include <stdint.h>

# include "libft/includes/libft.h"

typedef uint32_t	t_uint;
typedef uint8_t		t_uchar;

/*
** File Management
*/

typedef enum	e_status
{
	st_ok = 0,
	st_eof = 1,
	st_err = 2,
}				t_status;

typedef struct	s_file
{
	size_t		size;
	int			fd;
	t_status	status;
	int			err;
	bool		padding_finished;
}				t_file;

t_file			open_file(char *name);
int				read_safe(t_file *file, t_uchar *buffer, int size);
bool			read_padded(t_file *file, t_uchar *buffer);

/*
** Dispatching
*/

typedef struct	s_args
{
	char		*module;
	char		**argv;
	int			argc;
	int			err;
	bool		quiet:1;
	bool		print_stdin:1;
	bool		reversed:1;
}				t_args;

typedef void	(*t_module_fn)(t_args *args, t_file *file);

typedef struct	s_module
{
	char		*name;
	t_module_fn	fn;
}				t_module;

t_args			get_args(int argc, char **argv);

/*
** Encoding
*/

# define MD5_BLOCK 64
# define MD5_PAD 56
# define MD5_VARS 4

typedef enum	e_md5_fun
{
	fun_f,
	fun_g,
	fun_h,
	fun_i,
}				t_md5_fun;

/*
** Describes on of the 64 pass over the data
** According to the formula:
** var[s.ivar[0]] =
**     var[s.ivar[1]] + ((
**         var[s.ivar[0]]
**         + s.fun(var[s.ivar[1]],var[s.ivar[2]],var[s.ivar[3]])
**         + data[s.idata] + consts[i]
**     ) <<< s.bits)
*/

typedef struct	s_md5_pass
{
	t_md5_fun	fun:8;
	t_uchar		ivar[4];
	t_uint		idata:8;
	t_uint		bits:8;
}				t_md5_pass;

void			module_md5(t_args *args, t_file *file);

# define SHA256_BLOCK 64
# define SHA256_PAD 56
# define SHA256_VARS 8

void			module_sha256(t_args *args, t_file *file);

#endif
