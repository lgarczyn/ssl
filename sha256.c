/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 03:09:08 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/22 19:05:22 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static t_uint g_consts[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

#define CH(x, y, z)			(((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z)		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define EP0(x)				(RR(x, 2) ^ RR(x, 13) ^ RR(x, 22))
#define EP1(x)				(RR(x, 6) ^ RR(x, 11) ^ RR(x, 25))
#define SIG0(x)				(RR(x, 7) ^ RR(x, 18) ^ ((x) >> 3))
#define SIG1(x)				(RR(x, 17) ^ RR(x, 19) ^ ((x) >> 10))

#define RR(val, shift)		(((val) >> (shift)) | ((val) << (32 - (shift))))

static void		pass(const t_uint *data, t_uint *var)
{
	int			i;
	t_uint		m[64];
	t_uint		t1;
	t_uint		t2;

	i = -1;
	while (++i < 64)
		if (i < 16)
			m[i] = READ32_BIG_E(data[i]);
		else
			m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	i = -1;
	while (++i < 64)
		m[i] += + g_consts[i];
	i = -1;
	while (++i < 64)
	{
		t1 = var[7] + EP1(var[4]) + CH(var[4], var[5], var[6])
			+ m[i];
		t2 = EP0(var[0]) + MAJ(var[0], var[1], var[2]);
		ft_memmove(var + 1, var, sizeof(*var) * 7);
		var[4] += t1;
		var[0] = t1 + t2;
	}
}

void			module_sha256(t_args *args, t_file *file)
{
	t_uchar		buffer[SHA256_BLOCK];
	t_uint		vars[SHA256_VARS];
	t_uint		tmp_vars[SHA256_VARS];
	int			i;

	(void)args;
	ft_memcpy(
		vars,
		(t_uint[SHA256_VARS]){
			0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
			0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19},
		sizeof(vars));
	while (read_padded(file, buffer, big_endian))
	{
		ft_memcpy(tmp_vars, vars, sizeof(vars));
		pass((t_uint*)buffer, vars);
		i = -1;
		while (++i < SHA256_VARS)
			vars[i] += tmp_vars[i];
	}
	i = -1;
	while (++i < SHA256_VARS)
		printf("%08x", vars[i]);
	printf(" a\n");
}
