/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:51:39 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 14:31:16 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env_after_cd(t_env *env)
{
	char	pwd[5120];

	getcwd(pwd, 5120);
	if (pwd[0] != '\0')
	{
		if (!name_is_in_env(env, "OLDPWD"))
			env_change_value_by_name(env, "OLDPWD",
				ft_strdup(env_get_value(env, "PWD")));
		else
			set_env_export(env, ft_strdup("OLDPWD"), \
					env_get_value(env, "PWD"), 1);
		env_change_value_by_name(env, "PWD", ft_strdup(pwd));
		free(env->prompt);
		env->prompt = set_prompt(env, env_get_value(env, "USER"));
	}
}

void	call_cd(t_env *env, char **arg)
{
	int		i;
	char	buf[4086];

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
		g_status = return_error("cd", " : too many arguments\n", 1);
	else if ((arg[1] == NULL || ft_strcmp(arg[1], "--") == 0 \
		|| ft_strcmp(arg[1], "~") == 0) && env_get_value(env, "HOME"))
		chdir(env_get_value(env, "HOME"));
	else if (ft_strcmp(arg[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(arg[1], "-") == 0 && env_get_value(env, "OLDPWD"))
		chdir(env_get_value(env, "OLDPWD"));
	else if (ft_strcmp(arg[1], ".") == 0 && env_get_value(env, "PWD"))
		chdir(env_get_value(env, "PWD"));
	else
		chdir(arg[1]);
	getcwd(buf, 4086);
	if (errno)
		g_status = return_error(arg[1], ": No such file or directory\n", 1);
	set_env_after_cd(env);
	if (ft_strcmp(arg[1], "-") == 0)
		printf("%s\n", env_get_value(env, "PWD"));
}
