/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:40:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/10 02:00:12 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SSL_H
# define __SSL_H

# include <stdbool.h>

# include "libft/includes/libft.h"

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

typedef int		(*t_module_fn)(t_args *args);

typedef struct	s_module
{
	char		*name;
	t_module_fn	fn;
}				t_module;

t_args			get_args(int argc, char **argv);

int				*module_md5(t_args *args);
int				*module_sha256(t_args *args);

int				read_safe(int fd, char *buffer, int size);

#endif
