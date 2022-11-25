/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:47:00 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 14:35:35 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned char	g_status;

void	ft_strcat_here(char **dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[0][i])
		i++;
	while (src[j])
	{
		dest[0][i] = src[j];
		i++;
		j++;
	}
}

char	*set_prompt(t_env *env, char *value)
{
	char		*ret;
	char		*tmp;
	size_t		len;

	if (!value)
		value = "user_tmp";
	ret = NULL;
	tmp = env_get_value(env, "PWD");
	if (!tmp)
		tmp = "(null)";
	len = ft_strlen(value) + ft_strlen(BLUE) + ft_strlen(RESET)
		+ ft_strlen(GREEN) + ft_strlen(tmp) + 5;
	ret = (char *)malloc(sizeof(char) * (len));
	ft_bzero(ret, len);
	ft_strcat_here(&ret, GREEN);
	ft_strcat_here(&ret, value);
	ft_strcat_here(&ret, "@");
	ft_strcat_here(&ret, ":");
	ft_strcat_here(&ret, BLUE);
	ft_strcat_here(&ret, tmp);
	ft_strcat_here(&ret, RESET);
	ft_strcat_here(&ret, "$ ");
	return (ret);
}

void	while_read(t_env *env)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline(env->prompt);
		add_history(line);
		tmp = line;
		line = ft_strtrim(line, " \t\v\n\r");
		free(tmp);
		if (line == NULL && printf("exit\n"))
			break ;
		if (line[0] == '\0' && ft_free_this((void **)&line))
			continue ;
		if (!line && printf("\n"))
			continue ;
		if (check_line(line, -1) && ft_free_this((void **)&line))
			continue ;
		set_list_pipe_redir(env, line);
		if (!meta_char_change(env, &line) && ft_free_this((void **)&line))
			continue ;
		check_redirection(env, line);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	g_status = 0;
	if (ac != 1 && av != NULL)
	{
		ft_putstr_fd(2, RED"ERROR! Usage : ./minishell\n"RESET);
		return (FAILURE);
	}
	if (handle_signal() == ERROR)
		return (FAILURE);
	init_env(envp, &env);
	if (env.in_env == NULL)
	{
		ft_putstr_fd(2, "env: error: no environment\n");
		return (1);
	}
	env.save_stdin = dup(0);
	env.save_stdout = dup(1);
	handle_shlvl(&env);
	env.prompt = set_prompt(&env, env_get_value(&env, "USER"));
	while_read(&env);
	free_all(&env);
	return (SUCCESS);
}
