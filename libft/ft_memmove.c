/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:46:35 by mdupuis           #+#    #+#             */
/*   Updated: 2021/07/05 11:55:11 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*mem_dst;
	unsigned char	*mem_src;

	i = 0;
	mem_dst = (unsigned char *)dst;
	mem_src = (unsigned char *)src;
	if (src == dst)
		return (dst);
	if (mem_src < mem_dst)
	{
		while (++i <= size)
			mem_dst[size - i] = mem_src[size - i];
	}
	else
		ft_memcpy(dst, src, size);
	return (dst);
}
