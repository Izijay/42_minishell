/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:14:45 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 15:39:56 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_quote_while(char *line, int *i, int *j, int *quote)
{
	while (line[*i + *j])
	{
		if (line[*i + *j] == '\'')
		{
			*quote += 1;
			if (*quote % 2 == 0)
				break ;
		}
		if (line[*i + *j] == ' ')
			line[*i + *j] = '\a';
		*j += 1;
	}
}

int	parsing_quote(char *line, int *i, char **ret)
{
	int		j;
	int		quote;
	char	*tmp;
	char	*value;

	tmp = NULL;
	j = 1;
	quote = 1;
	parsing_quote_while(line, i, &j, &quote);
	if (quote == 1)
		return (0);
	value = ft_substr(line, *i + 1, j - 1);
	tmp = ft_strndup(line, *i);
	if (!(*value) && (*i == 0 || line[*i - 1] == ' ') && line[*i + 2] == ' ')
		tmp = ft_freejoin(tmp, "\f");
	else
		tmp = ft_freejoin(tmp, value);
	if (line[*i + j + 1])
		tmp = ft_freejoin(tmp, line + *i + j + 1);
	if (value)
		j--;
	*i += j;
	free(value);
	fill_ret(ret, &value, tmp);
	return (1);
}
