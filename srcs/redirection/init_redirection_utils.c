/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:08:15 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 16:47:19 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_file_and_place_args(char **line, int i, int ret, char **split)
{
	int		j;

	(void)ret;
	j = 1;
	if (i == -1)
		i = 0;
	else if (i == 0 && ret)
		i++;
	while (split[j] != NULL)
	{
		ft_strcat((*line) - i - 1, split[j]);
		j++;
	}
	return (split[0]);
}

int	get_command_pos(t_env *env, t_redirection *redirection)
{
	t_redirection	*tmp;
	int				first;

	first = 0;
	tmp = env->redirection;
	while (tmp)
	{
		if (tmp->pipe_valid == redirection->pipe_valid)
			break ;
		tmp = tmp->next;
	}
	if (tmp->index == 0)
		first++;
	return (redirection->index - tmp->index + tmp->double_redirection - first);
}

int	setup_redirection_helper(t_env *env, char **line,
	t_redirection *redirection, int f(t_env*, char*))
{
	int		i;
	char	*tmp;
	int		ret;
	char	**split;

	i = 0;
	if (((*line)[i] == '<' && (*line)[i + 1] == '<')
			|| ((*line)[i] == '>' && (*line)[i + 1] == '>'))
				(*line)[i++] = '\0';
	(*line)[i++] = '\0';
	(*line) += i;
	ret = put_end_on_redirection((*line));
	tmp = ft_strndup((*line), ret);
	split = ft_split_str(tmp, " \t\v\n\r");
	pipe_reverse_magic(split, '\a', ' ');
	(*line) = get_file_and_place_args((line),
			get_command_pos(env, redirection),
			env->redirection->double_redirection, split);
	if (f(env, (*line)))
	{
		free_free(split, tmp);
		return (0);
	}
	free_free(split, tmp);
	return (ret + i - 1);
}

int	setup_redirection(t_env *env, char *line, int f(t_env*, char*),
		t_redirection **redir)
{
	int				i;
	int				ret;
	t_redirection	*redirection;

	redirection = *redir;
	i = 0;
	if (redirection && redirection->valid)
	{
		ret = setup_redirection_helper(env, &line, redirection, f);
		redirection = redirection->next;
		*redir = redirection;
		return (ret);
	}
	redirection = redirection->next;
	*redir = redirection;
	if ((line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>'))
		return (2);
	return (1);
}

int	create_redirection(t_env *env, int adress, char valid, char *line)
{
	t_redirection	*new;
	t_redirection	*tmp;

	new = (t_redirection *)malloc(sizeof(t_redirection));
	if (new == NULL)
		return (FAILURE);
	ft_bzero(new, sizeof(t_redirection));
	new->index = adress;
	new->valid = valid;
	new->pipe_valid = env->valid_pipe_count;
	if (line[adress + 1] == '>' || line[adress + 1] == '<')
		new->double_redirection = 1;
	else
		new->double_redirection = 0;
	new->next = NULL;
	tmp = env->redirection;
	if (tmp == NULL)
		env->redirection = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}
