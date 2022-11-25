/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:35:34 by mdupuis           #+#    #+#             */
/*   Updated: 2022/04/20 13:19:49 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_unset(t_env *env, char *line)
{
	char	**arg;

	arg = ft_split(line, ' ');
	env_delete_by_name(env, arg[1]);
	ft_free_tab2d(arg);
	g_status = 0;
}
