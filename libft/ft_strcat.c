/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:47:20 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 00:26:32 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		if (src[j] == ' ')
			dest[i + j] = '\a';
		else
			dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = ' ';
	dest[i + j + 1] = '\0';
	return (dest);
}
