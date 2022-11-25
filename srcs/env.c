/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:58:41 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/02 16:18:08 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_in_env	*creat_node(void)
{
	t_in_env	*new;

	new = malloc(sizeof(t_in_env));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, sizeof(t_in_env));
	return (new);
}

void	free_all(t_env *env)
{
	t_in_env	*tmp;

	while (env->in_env)
	{
		if (env->in_env->name)
			free(env->in_env->name);
		if (env->in_env->value)
			free(env->in_env->value);
		tmp = env->in_env;
		env->in_env = env->in_env->next;
		free(tmp);
	}
	free(env->prompt);
	exit (g_status);
}

void	split_env(char *str, t_in_env *new)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	new->name = ft_strndup(str, (size_t)i);
	new->value = ft_strdup(str + i + 1);
}	

/**
 * It takes the environment
 * variables from the main function and puts them into a linked list
 */

void	init_env(char **envp, t_env *env)
{
	int			i;
	t_in_env	*new;

	i = -1;
	ft_bzero(env, sizeof(t_env));
	while (envp[++i])
	{
		new = creat_node();
		if (new == NULL)
			free_all(env);
		split_env(envp[i], new);
		new->equal = 1;
		if (!new->name || !new->value)
			free_all(env);
		if (env->in_env == NULL)
		{
			env->in_env = new;
			new->next = NULL;
		}
		else
		{
			new->next = env->in_env;
			env->in_env = new;
		}
	}
}

void	handle_shlvl(t_env *env)
{
	char	*value;
	int		shlvl;

	shlvl = 0;
	if (name_is_in_env(env, "SHLVL") == FAILURE)
	{
		value = ft_itoa(1);
		set_env_export(env, ft_strdup("SHLVL"), ft_strdup(value), 1);
		free(value);
		return ;
	}
	value = env_get_value(env, "SHLVL");
	if (value)
		shlvl = ft_atoi(value);
	shlvl++;
	value = ft_itoa(shlvl);
	env_change_value_by_name(env, "SHLVL", ft_strdup(value));
	free(value);
}
