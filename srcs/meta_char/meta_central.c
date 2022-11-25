/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_central.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:53:37 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/07 15:16:46 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	pars(char **line, char **ret, int b_dollar)
{
	if (*line)
	{
		if (b_dollar != 666)
			free(*line);
		*line = ft_strdup(*ret);
		free(*ret);
		*ret = NULL;
	}
	return ((1 + 2 - 3 + 1) % 100);
}

int	meta_char_quote(char **ret, int *i, char **mine)
{
	if (parsing_quote(*mine, i, ret) && pars(mine, ret, 0))
		return (1);
	else
	{
		ft_putstr_fd(2, "Minishell: Mismatching quote.\n");
		return (0);
	}
}

int	meta_char_dbl_quote(t_env *env, char **mine, int *i, char **ret)
{
	int	b_dollar;

	b_dollar = parsing_dbl_quotes(env, *mine, i, ret);
	if (b_dollar && pars(mine, ret, b_dollar))
		return (1);
	else
	{
		ft_putstr_fd(2, "Minishell: Mismatching quote.\n");
		return (0);
	}
}

int	meta_char_helper(t_env *env, t_pabo *g, char **line)
{
	if (g->mine[g->i] == '\'')
	{
		if (meta_char_quote(&g->ret, &g->i, &g->mine))
			return (1);
		free(g->mine);
		*line = NULL;
		return (0);
	}
	if (g->mine[g->i] == '"')
	{
		if (meta_char_dbl_quote(env, &g->mine, &g->i, &g->ret))
			return (1);
		*line = NULL;
		return (0);
	}
	return (0);
}

int	meta_char_change(t_env *env, char **line)
{	
	t_pabo	g;

	init_var_meta_char(&g, line);
	while (g.mine[g.i])
	{
		if (g.mine[g.i] == '$' && g.mine[g.i + 1] == '?')
			if (meta_char_dollar_question(env, &g.i, &g.ret, g.mine)
				&& pars(&g.mine, &g.ret, 0))
				continue ;
		if (g.mine[g.i] == '$')
			if (pars_dol(env, g.mine, &g.i, &g.ret) && pars(&g.mine, &g.ret, 0))
				continue ;
		if (g.mine[g.i] == '\'' || g.mine[g.i] == '"')
		{
			if (meta_char_helper(env, &g, line))
				continue ;
			return (0);
		}
		g.i++;
	}
	*line = g.mine;
	return (2);
}
