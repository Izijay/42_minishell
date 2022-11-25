/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:18:46 by mdupuis           #+#    #+#             */
/*   Updated: 2021/07/05 11:40:28 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_atoi(const char *str, int *i)
{
	int	sig;

	sig = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		*i = *i + 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sig = sig * -1;
		*i = *i + 1;
	}
	return (sig);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sig;
	int		i;
	int		ret;

	i = 0;
	res = 0;
	ret = 1;
	sig = ft_check_atoi(str, &i);
	str += i;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + *str++ - 48;
		if (res < 0 && (sig == 1 || sig == -1))
		{
			if (sig == 1)
				ret = -1;
			else
				ret = 0;
		}
	}
	if (ret == 1)
		return (res * sig);
	return (ret);
}
