/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:57:28 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 15:01:53 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file_redirection_helper_out(t_env *env, char **line, int *i,
	t_redirection **redirection)
{
	int		ret;

	if ((*line)[*i] == '>' && (*line)[*i + 1] == '>')
	{
		ret = setup_redirection(env, *line + *i,
				redirection_out_append, redirection);
		if (!ret)
			return (1);
		*i += ret;
	}
	if ((*line)[*i] == '>')
	{
		ret = setup_redirection(env, *line + *i,
				redirection_out, redirection);
		if (!ret)
			return (1);
		*i += ret;
	}
	return (0);
}

int	check_file_redirection_helper_in(t_env *env, char **line, int *i,
	t_redirection **redirection)
{
	int		ret;

	if ((*line)[*i] == '<' && (*line)[*i + 1] == '<')
	{
		ret = setup_redirection(env, *line + *i, redirection_here_document,
				redirection);
		if (!ret && ft_free_this((void **)line))
			return (1);
		*i += ret;
	}
	if ((*line)[*i] == '<')
	{
		ret = setup_redirection(env, *line + *i, redirection_in, redirection);
		if (!ret)
			return (1);
		*i += ret;
	}
	return (0);
}

int	free_free(char **split, char *tmp)
{
	ft_free_tab2d(split);
	free(tmp);
	return (1);
}
