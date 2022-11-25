/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:58:43 by mdupuis           #+#    #+#             */
/*   Updated: 2022/04/12 22:46:06 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_env(t_env *env)
{
	t_in_env	*tmp;

	tmp = env->in_env;
	while (tmp->next != NULL)
	{
		printf("%s", tmp->name);
		if (tmp->equal)
			printf("=%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}
