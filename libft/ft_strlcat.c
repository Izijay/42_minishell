/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:56:42 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/07 17:47:11 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const char	*sr;
	char		*dst;
	size_t		n;
	size_t		len;

	dst = dest;
	sr = src;
	n = size;
	while (n-- != 0 && *dst != '\0')
		dst++;
	len = dst - dest;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(sr));
	while (*sr != '\0')
	{
		if (n != 1)
		{
			*dst++ = *sr;
			n--;
		}
		sr++;
	}
	*dst = '\0';
	return (len + (sr - src));
}
