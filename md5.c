/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 03:09:14 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/07/10 04:29:42 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void			module_md5(t_args *args, t_file *file)
{
	char		buffer[MD5_BLOCK + 1];

	(void)args;
	buffer[MD5_BLOCK] = '\0';
	while (read_md5(file, buffer))
	{
		printf("%s\n", buffer);
	}
	printf("%s\n", buffer);
	//find some other way
}
