/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:02:08 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 15:51:39 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_paclean	init_paclean(t_env *env, int *i, char *line, char **ret)
{
	t_paclean	paclean;

	paclean.i = i;
	paclean.j = 1;
	paclean.line = line;
	paclean.quote = 1;
	paclean.ret = ret;
	paclean.env = env;
	return (paclean);
}

static void	parsing_dbl_quotes_while(t_paclean *f, int i, int k)
{
	k = i;
	while (f->line[i + f->j])
	{
		if (f->line[i + f->j] == '$' && ft_isalpha(f->line[i + f->j + 1]))
		{
			i += f->j;
			if (pars_dol(f->env, f->line, &i, f->ret))
			{
				free(f->line);
				f->line = ft_strdup(*f->ret);
				free(*f->ret);
				i = k;
				*f->ret = NULL;
				f->j = 1;
				continue ;
			}
		}
		if (f->line[i + f->j] == ' ')
				f->line[i + f->j] = '\a';
		if (f->line[k + f->j] == '"')
			if (++f->quote % 2 == 0)
				break ;
		f->j++;
	}
}

int	check_line_quote(char **line, t_paclean *f, int *b_dollar)
{
	if (*line != f->line)
	{
		*b_dollar = 666;
		*line = ft_strdup(f->line);
		free(f->line);
	}
	if (f->quote == 1)
	{
		if (*b_dollar)
			free(*line);
		return (0);
	}
	return (1);
}

int	parsing_dbl_quotes(t_env *env, char *line, int *i, char **ret)
{
	char		*tmp;
	char		*value;
	int			b_dollar;
	t_paclean	f;

	tmp = NULL;
	f = init_paclean(env, i, line, ret);
	b_dollar = 1;
	parsing_dbl_quotes_while(&f, *i, 0);
	if (!check_line_quote(&line, &f, &b_dollar))
		return (0);
	value = ft_substr(line, *i + 1, f.j - 1);
	tmp = ft_strndup(line, *i);
	pars_dbl_quote(line, i, value, &tmp);
	if (line[*i + f.j + 1])
		tmp = ft_freejoin(tmp, line + *i + f.j + 1);
	if (value)
		f.j--;
	*i += f.j;
	free(value);
	fill_ret(ret, &value, tmp);
	if (b_dollar == 666)
		free(line);
	return (b_dollar);
}
