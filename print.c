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

void		print_hash(t_uint *vars, t_uint size, t_endian endian, t_args *args)
{
	t_uint	i;

	i = 0;
	while (i < size)
		print_uint(vars[i++], endian);
	ft_putchar('\n');
	(void)args;
}