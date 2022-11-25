/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:02:58 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 23:56:10 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list_pipe_redirection(t_env *env)
{
	t_pipe			*pipe_tmp;
	t_redirection	*redirection_tmp;

	while (env->pipe)
	{
		pipe_tmp = env->pipe;
		env->pipe = env->pipe->next;
		free(pipe_tmp);
		pipe_tmp = NULL;
	}
	while (env->redirection)
	{
		redirection_tmp = env->redirection;
		env->redirection = env->redirection->next;
		free(redirection_tmp);
		redirection_tmp = NULL;
	}
	env->valid_pipe_count = 0;
}

t_redirection	*get_redirection_from_pos(t_env *env, int pos)
{
	t_redirection	*redirection;

	redirection = env->redirection;
	while (redirection)
	{
		if (redirection->pipe_valid == pos)
			break ;
		redirection = redirection->next;
	}
	return (redirection);
}

int	check_file_redirection(t_env *env, char *line, int pos, int i)
{
	t_redirection	*redirection;

	redirection = get_redirection_from_pos(env, pos);
	if (!redirection)
		return (SUCCESS);
	while (line[i])
	{
		if (line[i] == '>')
		{
			if (check_file_redirection_helper_out(env, &line, &i, &redirection))
				return (FAILURE);
			continue ;
		}
		if (line[i] == '<')
		{
			if (check_file_redirection_helper_in(env, &line, &i, &redirection))
				return (FAILURE);
			continue ;
		}
		i++;
	}
	return (SUCCESS);
}

void	error_exit(t_env *env, const char *message)
{
	perror(message);
	free_all(env);
	exit(FAILURE);
}

void	set_list_pipe_redir(t_env *env, char *line)
{
	int		i;

	i = 0;
	free_list_pipe_redirection(env);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (!is_between_quote(line, i))
				create_pipe(env, i - 1, 1);
			else
				create_pipe(env, i - 1, 0);
		}
		if (((line[i] == '>' ) || (line[i] == '<')))
		{
			if (!is_between_quote(line, i))
				create_redirection(env, i, 1, line);
			else
				create_redirection(env, i, 0, line);
			if ((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
				i++;
		}
		i++;
	}
}
