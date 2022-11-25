/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:53:12 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/12 18:34:27 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	put_end_on_redirection(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			return (i);
		i++;
	}
	return (i);
}

int	redirection_out(t_env *env, char *file)
{
	int		fd;

	(void)env;
	if (file == NULL)
	{
		g_status = return_error(":", "No such file or directory\n", 1);
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		g_status = return_error("open", " failed\n", 1);
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		g_status = return_error("dup2", " failed\n", 1);
		return (1);
	}
	return (0);
}

int	redirection_in(t_env *env, char *file)
{
	int		fd;

	(void)env;
	if (file == NULL)
	{
		g_status = return_error(":", "No such file or directory\n", 1);
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		g_status = return_error("open", " failed\n", 1);
		return (1);
	}
	if (dup2(fd, 0) == -1)
	{
		g_status = return_error("dup2", " failed\n", 1);
		return (1);
	}
	return (0);
}

int	redirection_out_append(t_env *env, char *file)
{
	int		fd;

	(void)env;
	if (file == NULL)
	{
		g_status = return_error(":", "No such file or directory\n", 1);
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		g_status = return_error("open", " failed\n", 1);
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		g_status = return_error("dup2", " failed\n", 1);
		return (1);
	}
	return (0);
}

int	check_redirection(t_env *env, char *line)
{
	char			**split;

	env->save_stdin = dup(0);
	env->save_stdout = dup(1);
	line = pipe_magic(env, line);
	split = ft_splitrim(line, '|');
	if (split[0] == NULL)
		return (FAILURE);
	pipe_reverse_magic(split, '\n', '|');
	test_recu(env, split, 0, STDIN_FILENO);
	dup2(env->save_stdin, 0);
	dup2(env->save_stdout, 1);
	while (wait(NULL) > 0)
		;
	ft_free_tab2d(split);
	return (SUCCESS);
}
