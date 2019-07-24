/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 03:09:14 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/22 19:05:34 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static t_md5_pass g_passes[64] = {
	{.fun = fun_f, .ivar = {0, 1, 2, 3}, .idata = 0, .bits = 7},
	{.fun = fun_f, .ivar = {3, 0, 1, 2}, .idata = 1, .bits = 12},
	{.fun = fun_f, .ivar = {2, 3, 0, 1}, .idata = 2, .bits = 17},
	{.fun = fun_f, .ivar = {1, 2, 3, 0}, .idata = 3, .bits = 22},
	{.fun = fun_f, .ivar = {0, 1, 2, 3}, .idata = 4, .bits = 7},
	{.fun = fun_f, .ivar = {3, 0, 1, 2}, .idata = 5, .bits = 12},
	{.fun = fun_f, .ivar = {2, 3, 0, 1}, .idata = 6, .bits = 17},
	{.fun = fun_f, .ivar = {1, 2, 3, 0}, .idata = 7, .bits = 22},
	{.fun = fun_f, .ivar = {0, 1, 2, 3}, .idata = 8, .bits = 7},
	{.fun = fun_f, .ivar = {3, 0, 1, 2}, .idata = 9, .bits = 12},
	{.fun = fun_f, .ivar = {2, 3, 0, 1}, .idata = 10, .bits = 17},
	{.fun = fun_f, .ivar = {1, 2, 3, 0}, .idata = 11, .bits = 22},
	{.fun = fun_f, .ivar = {0, 1, 2, 3}, .idata = 12, .bits = 7},
	{.fun = fun_f, .ivar = {3, 0, 1, 2}, .idata = 13, .bits = 12},
	{.fun = fun_f, .ivar = {2, 3, 0, 1}, .idata = 14, .bits = 17},
	{.fun = fun_f, .ivar = {1, 2, 3, 0}, .idata = 15, .bits = 22},
	{.fun = fun_g, .ivar = {0, 1, 2, 3}, .idata = 1, .bits = 5},
	{.fun = fun_g, .ivar = {3, 0, 1, 2}, .idata = 6, .bits = 9},
	{.fun = fun_g, .ivar = {2, 3, 0, 1}, .idata = 11, .bits = 14},
	{.fun = fun_g, .ivar = {1, 2, 3, 0}, .idata = 0, .bits = 20},
	{.fun = fun_g, .ivar = {0, 1, 2, 3}, .idata = 5, .bits = 5},
	{.fun = fun_g, .ivar = {3, 0, 1, 2}, .idata = 10, .bits = 9},
	{.fun = fun_g, .ivar = {2, 3, 0, 1}, .idata = 15, .bits = 14},
	{.fun = fun_g, .ivar = {1, 2, 3, 0}, .idata = 4, .bits = 20},
	{.fun = fun_g, .ivar = {0, 1, 2, 3}, .idata = 9, .bits = 5},
	{.fun = fun_g, .ivar = {3, 0, 1, 2}, .idata = 14, .bits = 9},
	{.fun = fun_g, .ivar = {2, 3, 0, 1}, .idata = 3, .bits = 14},
	{.fun = fun_g, .ivar = {1, 2, 3, 0}, .idata = 8, .bits = 20},
	{.fun = fun_g, .ivar = {0, 1, 2, 3}, .idata = 13, .bits = 5},
	{.fun = fun_g, .ivar = {3, 0, 1, 2}, .idata = 2, .bits = 9},
	{.fun = fun_g, .ivar = {2, 3, 0, 1}, .idata = 7, .bits = 14},
	{.fun = fun_g, .ivar = {1, 2, 3, 0}, .idata = 12, .bits = 20},
	{.fun = fun_h, .ivar = {0, 1, 2, 3}, .idata = 5, .bits = 4},
	{.fun = fun_h, .ivar = {3, 0, 1, 2}, .idata = 8, .bits = 11},
	{.fun = fun_h, .ivar = {2, 3, 0, 1}, .idata = 11, .bits = 16},
	{.fun = fun_h, .ivar = {1, 2, 3, 0}, .idata = 14, .bits = 23},
	{.fun = fun_h, .ivar = {0, 1, 2, 3}, .idata = 1, .bits = 4},
	{.fun = fun_h, .ivar = {3, 0, 1, 2}, .idata = 4, .bits = 11},
	{.fun = fun_h, .ivar = {2, 3, 0, 1}, .idata = 7, .bits = 16},
	{.fun = fun_h, .ivar = {1, 2, 3, 0}, .idata = 10, .bits = 23},
	{.fun = fun_h, .ivar = {0, 1, 2, 3}, .idata = 13, .bits = 4},
	{.fun = fun_h, .ivar = {3, 0, 1, 2}, .idata = 0, .bits = 11},
	{.fun = fun_h, .ivar = {2, 3, 0, 1}, .idata = 3, .bits = 16},
	{.fun = fun_h, .ivar = {1, 2, 3, 0}, .idata = 6, .bits = 23},
	{.fun = fun_h, .ivar = {0, 1, 2, 3}, .idata = 9, .bits = 4},
	{.fun = fun_h, .ivar = {3, 0, 1, 2}, .idata = 12, .bits = 11},
	{.fun = fun_h, .ivar = {2, 3, 0, 1}, .idata = 15, .bits = 16},
	{.fun = fun_h, .ivar = {1, 2, 3, 0}, .idata = 2, .bits = 23},
	{.fun = fun_i, .ivar = {0, 1, 2, 3}, .idata = 0, .bits = 6},
	{.fun = fun_i, .ivar = {3, 0, 1, 2}, .idata = 7, .bits = 10},
	{.fun = fun_i, .ivar = {2, 3, 0, 1}, .idata = 14, .bits = 15},
	{.fun = fun_i, .ivar = {1, 2, 3, 0}, .idata = 5, .bits = 21},
	{.fun = fun_i, .ivar = {0, 1, 2, 3}, .idata = 12, .bits = 6},
	{.fun = fun_i, .ivar = {3, 0, 1, 2}, .idata = 3, .bits = 10},
	{.fun = fun_i, .ivar = {2, 3, 0, 1}, .idata = 10, .bits = 15},
	{.fun = fun_i, .ivar = {1, 2, 3, 0}, .idata = 1, .bits = 21},
	{.fun = fun_i, .ivar = {0, 1, 2, 3}, .idata = 8, .bits = 6},
	{.fun = fun_i, .ivar = {3, 0, 1, 2}, .idata = 15, .bits = 10},
	{.fun = fun_i, .ivar = {2, 3, 0, 1}, .idata = 6, .bits = 15},
	{.fun = fun_i, .ivar = {1, 2, 3, 0}, .idata = 13, .bits = 21},
	{.fun = fun_i, .ivar = {0, 1, 2, 3}, .idata = 4, .bits = 6},
	{.fun = fun_i, .ivar = {3, 0, 1, 2}, .idata = 11, .bits = 10},
	{.fun = fun_i, .ivar = {2, 3, 0, 1}, .idata = 2, .bits = 15},
	{.fun = fun_i, .ivar = {1, 2, 3, 0}, .idata = 9, .bits = 21},
};

static t_uint g_consts[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

#define F(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)			(((x) ^ (y)) ^ (z))
#define I(x, y, z)			((y) ^ ((x) | ~(z)))

static t_uint	rotate_left(t_uint value, t_uint shift)
{
	return (value << shift) | (value >> (32 - shift));
}

__attribute__ ((hot))
static void		pass(const t_uint *data, t_uint *vars)
{
	t_uint		r;
	int			i;
	t_md5_pass	s;

	i = 0;
	while (i < 64)
	{
		s = g_passes[i];
		r = 0;
		if (s.fun == fun_f)
			r = F(vars[s.ivar[1]], vars[s.ivar[2]], vars[s.ivar[3]]);
		else if (s.fun == fun_g)
			r = G(vars[s.ivar[1]], vars[s.ivar[2]], vars[s.ivar[3]]);
		else if (s.fun == fun_h)
			r = H(vars[s.ivar[1]], vars[s.ivar[2]], vars[s.ivar[3]]);
		else if (s.fun == fun_i)
			r = I(vars[s.ivar[1]], vars[s.ivar[2]], vars[s.ivar[3]]);
		vars[s.ivar[0]] = vars[s.ivar[1]] + rotate_left(
				vars[s.ivar[0]]
					+ r
					+ READ32_SMALL_E(data[s.idata])
					+ g_consts[i],
				s.bits);
		i++;
	}
}

__attribute__ ((hot))
void			module_md5(t_args *args, t_file *file)
{
	t_uchar		buffer[MD5_BLOCK];
	t_uint		vars[MD5_VARS];
	t_uint		tmp_vars[MD5_VARS];
	int			i;

	(void)args;
	ft_memcpy(
		vars,
		(t_uint[MD5_VARS]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476},
		sizeof(vars));
	while (read_padded(file, buffer, little_endian))
	{
		ft_memcpy(tmp_vars, vars, sizeof(vars));
		pass((t_uint*)buffer, vars);
		i = -1;
		while (++i < MD5_VARS)
			vars[i] += tmp_vars[i];
	}
	i = -1;
	while (++i < (int)sizeof(vars))
		printf("%02x", (t_uint)((unsigned char*)vars)[i]);
	printf("\n");
}
