/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:44:38 by mdupuis           #+#    #+#             */
/*   Updated: 2021/07/05 11:54:08 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t					i;
	const unsigned char		*mem_s1;
	const unsigned char		*mem_s2;

	i = 0;
	mem_s1 = (const unsigned char *)s1;
	mem_s2 = (const unsigned char *)s2;
	while (i < size)
	{
		if (mem_s1[i] != mem_s2[i])
			return (mem_s1[i] - mem_s2[i]);
		i++;
	}
	return (0);
}
