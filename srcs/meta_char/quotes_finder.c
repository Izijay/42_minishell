/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:47:26 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 16:49:35 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pars_dbl_quote(char *line, int *i, char *value, char **tmp)
{
	if (!(*value) && (*i == 0 || line[*i - 1] == ' ') && line[*i + 2] == ' ')
		*tmp = ft_freejoin(*tmp, "\f");
	else
		*tmp = ft_freejoin(*tmp, value);
}

int	check_other_quote(char *str, int i, int pos, char quote)
{
	int		j;

	j = 1;
	while (str[i + j])
	{
		if (i + j == pos)
			return (0);
		if (str[i + j] == quote)
			break ;
		j++;
	}
	return (j);
}

int	is_between_quote(char *str, int pos)
{
	int		i;
	int		ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			ret = check_other_quote(str, i, pos, '\'');
			if (!ret)
				return (1);
			i += ret;
		}
		if (str[i] == '\"')
		{
			ret = check_other_quote(str, i, pos, '\"');
			if (!ret)
				return (1);
			i += ret;
		}
		if (str[i])
			i++;
	}
	return (0);
}
