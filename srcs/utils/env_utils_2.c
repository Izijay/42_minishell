/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:12:11 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 16:37:29 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_in_len(t_env *env)
{
	t_in_env	*tmp;
	int			len;

	len = 0;
	tmp = env->in_env;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len + 1);
}

char	*env_get_value(t_env *env, char *name)
{
	t_in_env	*tmp;

	tmp = env->in_env;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**env_get_new_envp(t_env *env)
{
	char		**new_envp;
	int			len;
	t_in_env	*tmp;
	int			i;

	len = ft_env_in_len(env);
	i = 0;
	new_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (new_envp == NULL)
		return (NULL);
	tmp = env->in_env;
	while (tmp)
	{
		new_envp[i] = ft_strdup(tmp->name);
		new_envp[i] = ft_freejoin(new_envp[i], "=");
		new_envp[i] = ft_freejoin(new_envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	new_envp[len] = NULL;
	return (new_envp);
}

int	name_is_in_env(t_env *env, char *name)
{
	t_in_env	*tmp;

	tmp = env->in_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

int	check_line(char *line, int i)
{
	int		juju;

	juju = 0;
	while (line[++i])
	{
		if (line[0] == '|')
			return (return_error(NULL, NULL, 2));
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>') \
					&& (!is_between_quote(line, i)))
		{
			butcher_code(line, &i, &juju);
			if (line[i] == '|' || line[i] == '<' || line[i] == '>' \
					|| line[i] == 0)
			{
				if (juju)
					continue ;
				return_err_token(line[i], 2);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}
