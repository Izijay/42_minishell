/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_set_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:27:38 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 22:58:49 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_pipe(t_env *env, int adress, char valid)
{
	t_pipe	*new;
	t_pipe	*tmp;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (new == NULL)
		return (FAILURE);
	new->index = adress;
	new->valid = valid;
	new->next = NULL;
	tmp = env->pipe;
	if (tmp == NULL)
		env->pipe = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (valid)
		env->valid_pipe_count++;
	return (SUCCESS);
}

void	test_recu_helper(t_env *env, char **split, int pos, int in_fd)
{
	int		fd[2];
	int		childpid;

	pipe(fd);
	childpid = fork();
	if (childpid == -1)
		error_exit(env, "Failed to setup pipe");
	if (childpid == 0)
	{
		close(fd[0]);
		if (dup2(in_fd, STDIN_FILENO) == -1
			|| dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[1]) == -1)
			error_exit(env, "Failed to redirect");
		else
		{
			if (!check_file_redirection(env, split[pos], pos, 0))
				check_call(split[pos], env);
			exit(0);
		}
	}
	close(fd[1]);
	close(in_fd);
	test_recu(env, split, pos + 1, fd[0]);
}

void	test_recu(t_env *env, char **split, int pos, int in_fd)
{
	if (split[pos + 1] == NULL)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1 || close(in_fd) == -1)
				error_exit(env, "Dup or close failed in the last call!");
		}
		if (!check_file_redirection(env, split[pos], pos, 0))
			check_call(split[pos], env);
	}
	else
		test_recu_helper(env, split, pos, in_fd);
}

char	*pipe_magic(t_env *env, char *line)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = env->pipe;
	while (tmp || line[i])
	{
		if (line[i] == '|')
		{
			if (!tmp->valid)
				line[i] = '\n';
			tmp = tmp->next;
		}
		i++;
	}
	return (line);
}

void	pipe_reverse_magic(char **split, char boldu, char harry)
{
	int		i;
	int		j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == boldu)
				split[i][j] = harry;
			j++;
		}
		i++;
	}
}
