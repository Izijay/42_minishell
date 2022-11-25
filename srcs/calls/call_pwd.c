/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:59:09 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/06 15:45:00 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_pwd(t_env *env, char **arg)
{
	(void)env;
	(void)arg;
	printf("%s\n", env_get_value(env, "PWD"));
	g_status = 0;
}
