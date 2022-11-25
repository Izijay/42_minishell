/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:11:36 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/12 11:46:55 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stdout_export_error(char *error)
{
	ft_putstr_fd(2, "Minishell: export: « ");
	ft_putstr_fd(2, error);
	ft_putstr_fd(2, " » : not a valid identifier\n");
	g_status = 1;
}

void	set_env_export(t_env *env, char *name, char *value, int equal)
{
	t_in_env	*new;

	new = creat_node();
	new->name = name;
	new->value = value;
	new->equal = equal;
	new->next = env->in_env;
	env->in_env = new;
}
