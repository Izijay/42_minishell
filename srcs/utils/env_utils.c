/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:00:24 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 13:24:35 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_change_value_export(t_env *env, char *line, int equal)
{
	char		*name;
	char		*value;
	t_in_env	*tmp;

	env_split_line_equal(line, &name, &value);
	tmp = env->in_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (!tmp->equal && equal)
				tmp->equal = equal;
			free(tmp->value);
			free(name);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	free(name);
	free(value);
}

void	env_delete_by_name_help(t_env *env)
{
	if (env->in_env->name)
		free(env->in_env->name);
	free(env->in_env->value);
	free(env->in_env);
}

void	env_delete_by_name(t_env *env, char *name)
{
	t_in_env	*tmp;
	t_in_env	*tmp2;

	tmp2 = env->in_env;
	tmp = env->in_env->next;
	if (ft_strcmp(env->in_env->name, name) == 0)
	{
		env_delete_by_name_help(env);
		env->in_env = tmp;
		return ;
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->name);
			free(tmp->value);
			tmp2->next = tmp->next;
			free(tmp);
			return ;
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
}

void	env_split_line_equal(char *line, char **name, char **value)
{
	int	i;

	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	name[0] = ft_strndup(line, (size_t)i);
	if (line[i])
		value[0] = ft_strdup(line + i + 1);
	else
		value[0] = ft_strdup("");
}

void	env_change_value_by_name(t_env *env, char *name, char *value)
{
	t_in_env	*tmp;

	tmp = env->in_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	free(value);
}
