/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:10:00 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/12 11:47:58 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_tab_export(char ***split)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (split[0][i])
	{
		j = i + 1;
		while (split[0][j])
		{
			if (ft_strcmp(split[0][i], split[0][j]) > 0)
			{
				tmp = split[0][i];
				split[0][i] = split[0][j];
				split[0][j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	call_export_noarg_help(char **split, t_env *env)
{
	int			i;
	t_in_env	*tmp;

	i = 0;
	tmp = env->in_env;
	while (tmp)
	{
		split[i] = ft_strdup("declare -x ");
		split[i] = ft_freejoin(split[i], tmp->name);
		if (tmp->equal)
		{
			split[i] = ft_freejoin(split[i], "=");
			split[i] = ft_freejoin(split[i], "\"");
			split[i] = ft_freejoin(split[i], tmp->value);
			split[i] = ft_freejoin(split[i], "\"");
		}
		tmp = tmp->next;
		i++;
	}
	split[i] = NULL;
}

static void	call_export_noarg(t_env *env)
{
	char		**split;
	int			len;
	int			i;

	i = -1;
	len = ft_env_in_len(env);
	split = (char **)malloc(sizeof(char *) * (len + 1));
	if (split == NULL)
		return ;
	call_export_noarg_help(split, env);
	sort_tab_export(&split);
	while (split[++i])
	{
		printf("%s\n", split[i]);
		free(split[i]);
	}
	free(split);
}

static int	check_export(char *to_check)
{
	int		i;

	i = 0;
	if (to_check[i] != '_' && !ft_isalpha(to_check[i]))
	{
		stdout_export_error(to_check);
		return (0);
	}
	while (to_check[i])
	{
		if (to_check[i] == '=')
			break ;
		if (to_check[i] != '_' && !ft_isalnum(to_check[i]))
		{
			stdout_export_error(to_check);
			return (0);
		}
		i++;
	}
	return (1);
}

void	call_export(t_env *env, char **tocheck)
{
	char		*name;
	char		*value;
	int			equal;
	int			i;

	i = 0;
	equal = 0;
	g_status = 0;
	while (tocheck[++i])
	{
		if (!check_export(tocheck[i]))
			continue ;
		env_split_line_equal(tocheck[i], &name, &value);
		if (ft_strchr(tocheck[i], '='))
			equal = 1;
		if (env_get_value(env, name) != NULL && ft_free_this((void **)&name))
		{
			free(value);
			env_change_value_export(env, tocheck[i], equal);
			return ;
		}
		set_env_export(env, name, value, equal);
	}
	if (i == 1)
		call_export_noarg(env);
}
