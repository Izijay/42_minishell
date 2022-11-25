/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 16:32:23 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 10:37:57 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_splitrim(const char *str, char c)
{
	char		**split;
	char		*tmp;
	int			i;

	split = ft_split(str, c);
	i = 0;
	while (split[i])
	{
		tmp = ft_strtrim(split[i], " \t\r");
		free(split[i]);
		split[i] = tmp;
		i++;
	}
	return (split);
}
