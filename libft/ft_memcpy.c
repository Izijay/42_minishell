/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:45:49 by mdupuis           #+#    #+#             */
/*   Updated: 2021/07/05 11:54:52 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*mem_dest;
	unsigned char	*mem_src;

	mem_dest = (unsigned char *)dest;
	mem_src = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (size--)
		*(mem_dest++) = *(mem_src++);
	return (dest);
}
