/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:03:51 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/07 15:20:31 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_the_towrite(char *here_doc)
{
	char	*towrite;
	char	*tmp;

	towrite = NULL;
	if ((here_doc == NULL || here_doc[0] == '<' || here_doc[0] == '>'
			|| here_doc[0] == '|') && printf("Minishell: syntax error near "
			"unexpected token\n"))
		return (NULL);
	while (1)
	{
		tmp = readline("> ");
		if (ft_strcmp(tmp, here_doc) == 0 && ft_free_this((void **)&tmp))
			break ;
		if (tmp == NULL && ft_free_this((void **)&tmp)
			&& printf("Minishell: warning : « here-document » "
				"is delimited by EOF (instead of « %s »)\n", here_doc))
			break ;
		if (!towrite)
			towrite = ft_strdup(tmp);
		else
			towrite = ft_freejoin(towrite, tmp);
		towrite = ft_freejoin(towrite, "\n");
		ft_free_this((void **)&tmp);
	}
	return (towrite);
}

char	*replace_dollar(t_env *env, char *line)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (line == NULL)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && ft_isalnum(line[i + 1]))
			pars_dol(env, line, &i, &ret);
		i++;
	}
	if (ret == NULL)
		ret = line;
	return (ret);
}

int	redirection_here_document(t_env *env, char *line)
{
	char	*strin;
	int		save_out;
	int		fd[2];
	int		child;

	save_out = dup(1);
	dup2(env->save_stdin, 0);
	pipe(fd);
	dup2(env->save_stdout, 1);
	strin = get_the_towrite(line);
	dup2(save_out, 1);
	strin = replace_dollar(env, strin);
	child = fork();
	if (child == 0)
	{
		dup2(fd[1], 1);
		write(fd[1], strin, ft_strlen(strin));
		exit(0);
	}
	else
		dup2(fd[0], 0);
	free(strin);
	dup2(env->save_stdin, fd[0]);
	dup2(1, fd[1]);
	return (0);
}
