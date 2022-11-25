/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:32 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/02 16:24:12 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	suppres_dollar(char *line, int *i, char **ret)
{
	char	*tmp;

	tmp = ft_strndup(line, *i);
	tmp = ft_freejoin(tmp, line + *i + 1);
	fill_ret(ret, NULL, tmp);
	return (1);
}

int	meta_char_dollar_question(t_env *env, int *i, char **ret, char *line)
{
	char	*value;
	char	*tmp;

	(void)env;
	value = ft_itoa(g_status);
	tmp = ft_strndup(line, *i);
	tmp = ft_freejoin(tmp, value);
	if (line[*i + 1])
		tmp = ft_freejoin(tmp, line + *i + 2);
	fill_ret(ret, &value, tmp);
	*i += ft_strlen(value);
	free(value);
	return (1);
}

/**
 * It parses the dollar sign
 * and replaces it with the value of the variable
 * 
 * @param env the environment
 * @param line the line to parse
 * @param i the index of the current character in the line
 * @param ret the string that will be returned
 * 
 * @return The function pars_dol is returning the value of the variable name.
 */
int	pars_dol(t_env *env, char *line, int *i, char **ret)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		j;

	j = 1;
	if ((line[*i + j] == '\'' || line[*i + j] == '"'))
		return (suppres_dollar(line, i, ret));
	while (line[*i + j] && line[*i + j] != ' ' && line[*i + j] != '\t'
		&& ft_isalnum(line[*i + j]))
			j++;
	if (j == 1)
		return (0);
	if (line[*i + j])
		j--;
	name = ft_strndup(line + *i + 1, j);
	value = env_get_value(env, name);
	tmp = ft_strndup(line, *i);
	tmp = ft_freejoin(tmp, value);
	if (line[*i + j])
		tmp = ft_freejoin(tmp, line + *i + j + 1);
	*i += ft_strlen(value);
	free(name);
	fill_ret(ret, &value, tmp);
	return (1);
}
