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

typedef uint64_t	t_usize;
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

typedef enum	e_type
{
	ty_file = 0,
	ty_stdin = 1,
	ty_string = 2,
}				t_type;

# define BUFFER_SIZE	(4096 * 32)

typedef struct	s_file
{
	t_uint		buffer_len;
	t_uint		buffer_pos;
	t_uchar		*buffer;
	char		*name;
	t_usize		size;
	int			fd;
	t_type		type;
	t_status	status;
	int			err;
	bool		padding_finished;
}				t_file;

typedef enum	e_endian
{
	little_endian,
	big_endian,
}				t_endian;

t_file			open_file(char *name);
t_file			open_stdin();
t_file			open_string(char *data);
void			close_file(t_file *file);
int				read_safe(t_file *file, t_uchar *buffer, t_uint size);
bool			read_padded(t_file *file, t_uchar *buffer, t_endian endian);

/*
** Endianness
*/

uint32_t					swap32(uint32_t v);
uint64_t					swap64(uint64_t v);

# if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#  define SYS_ENDIAN			(little_endian)
#  define READ32_SMALL_E(b)	((t_uint)b)
#  define READ32_BIG_E(b)	((t_uint)swap32((b)))
#  define READ64_SMALL_E(b)	((t_usize)b)
#  define READ64_BIG_E(b)	((t_usize)swap64((b)))
# else
#  define SYS_ENDIAN			(big_endian)
#  define READ32_SMALL_E(b)	((t_uint)swap32((b)))
#  define READ32_BIG_E(b)	((t_uint)b))
#  define READ64_SMALL_E(b)	((t_usize)swap64((b)))
#  define READ64_BIG_E(b)	((t_usize)b))
# endif

# define WRITE32_E(v, l)		(l == SYS_ENDIAN ? (t_uint)(v) : swap32(v))
# define WRITE64_E(v, l)		(l == SYS_ENDIAN ? (t_usize)(v) : swap64(v))

/*
** Dispatching
*/

struct s_args;

typedef void	(*t_module_fn)(struct s_args *args, t_file *file);

typedef struct	s_module
{
	char		*name;
	char		*display_name;
	t_module_fn	fn;
}				t_module;

typedef struct	s_args
{
	char		*path;
	char		**argv;
	int			argc;
	t_module	*module;
	int			err;
	bool		quiet:1;
	bool		print_stdin:1;
	bool		reversed:1;
	bool		take_input:1;
}				t_args;

t_args			get_args(int argc, char **argv);

/*
** Encoding
*/

# define MD5_BLOCK		64
# define MD5_PAD		56
# define MD5_VARS		4

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

# define SHA256_BLOCK	64
# define SHA256_PAD		56
# define SHA256_VARS	8

void			module_sha256(t_args *args, t_file *file);

#endif

/*
** Display
*/

void			print_hash(t_uint *vars, t_uint size, t_endian endian, t_file *file, t_args *args);