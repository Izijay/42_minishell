/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:52:09 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 16:55:51 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_call(char *line, t_env *env)
{
	if (line[0] == '\0')
	{
		g_status = return_error(line, ": command not found\n", 127);
		return ;
	}
	if (ft_strcmp("env", line) == 0)
		call_env(env);
	else
		parse_call(env, line);
}

int	ft_execute_child(char **arg, char *exec, t_env *env)
{
	pid_t	pid;
	char	**envp;
	int		wstatus;

	pid = fork();
	disable_signal(pid);
	if (pid == 0)
	{
		envp = env_get_new_envp(env);
		if (execve(exec, arg, envp) == -1)
		{
			ft_free_tab2d(envp);
			exit(check_exec(arg));
		}
		ft_free_tab2d(envp);
		exit(SUCCESS);
	}
	else if (pid < 0 && perror_help("Minishell"))
		return (ERROR);
	waitpid(pid, &wstatus, 0);
	g_status = handle_status(wstatus);
	handle_signal();
	return (SUCCESS);
}

char	*get_bin_path(t_env *env, char *arg, int i)
{
	char	*ret;
	char	**split_path;

	ret = NULL;
	if (arg[0] == '.' || arg[0] == '/')
		return (ft_strdup(arg));
	split_path = ft_split(env_get_value(env, "PATH"), ':');
	if (split_path == NULL && ft_free_this_tab2d(&split_path))
		return (NULL);
	while (split_path[i])
	{
		ret = ft_strdup(split_path[i]);
		ret = ft_freejoin(ret, "/");
		ret = ft_freejoin(ret, arg);
		if (access(ret, X_OK) == 0 && ft_free_this_tab2d(&split_path))
			return (ret);
		free(ret);
		i++;
	}
	ft_free_tab2d(split_path);
	return (ft_strdup(arg));
}

int	parse_call_helper(t_env *env, char **arg, char *exec)
{
	if ((name_is_in_env(env, "PATH") == FAILURE) && (arg[0][0] != '/'))
	{
		return_error(arg[0], " : No such file or directory\n", 127);
		ft_free_tab2d(arg);
		return (FAILURE);
	}
	exec = get_bin_path(env, arg[0], 0);
	if ((ft_execute_child(arg, exec, env)) == ERROR)
		if (g_status == 1)
			check_exec(arg);
	free(exec);
	return (SUCCESS);
}

void	parse_call(t_env *env, char *line)
{
	char	**arg;
	char	*exec;

	exec = NULL;
	arg = ft_split(line, ' ');
	pipe_reverse_magic(arg, '\a', ' ');
	pipe_reverse_magic(arg, '\f', '\0');
	if (arg == NULL)
		return ;
	if (ft_strcmp("export", arg[0]) == 0)
		call_export(env, arg);
	else if (ft_strcmp("unset", arg[0]) == 0)
		call_unset(env, line);
	else if (ft_strcmp("cd", arg[0]) == 0)
		call_cd(env, arg);
	else if (ft_strcmp("exit", arg[0]) == 0)
		call_exit(env, line);
	else if (ft_strcmp("pwd", arg[0]) == 0)
		call_pwd(env, arg);
	else if (ft_strcmp("echo", arg[0]) == 0)
		call_echo(env, arg, 1);
	else
		if (parse_call_helper(env, arg, exec) == FAILURE)
			return ;
	ft_free_tab2d(arg);
}
