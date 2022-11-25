/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:34 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/03 14:15:01 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncount(char *str, char c, int len)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && i < len)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
