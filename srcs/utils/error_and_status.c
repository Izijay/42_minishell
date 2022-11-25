/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:17:10 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 08:41:13 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_err_token(char token, int status)
{
	ft_putstr_fd(2, "Minishell: syntax error near unexpected token `");
	if (token)
		ft_putchar_fd(2, token);
	else
		ft_putstr_fd(2, "newline");
	ft_putstr_fd(2, "`\n");
	if (status >= 0)
		g_status = status;
	return (g_status);
}

int	return_error(char *cmd, char *msg, int status)
{
	if (status == 2 && cmd == NULL)
	{
		ft_putstr_fd(2, "Minishell: syntax error near unexpected token `|`\n");
		g_status = status;
		return (status);
	}
	ft_putstr_fd(2, "Minishell: ");
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, msg);
	if (status >= 0)
		g_status = status;
	return (g_status);
}

int	check_exec(char **args)
{
	struct stat	f;
	int			flag;

	if (lstat(args[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR)
			return (return_error(args[0], ": Is a directory\n", 126));
		else if ((ft_strncmp(args[0], "./", 2) || ft_strncmp(args[0], "/", 1))
			&& (f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
			return (42);
		else if (flag != S_IXUSR && flag != S_IRUSR
			&& flag != S_IFDIR && flag != S_IFLNK)
			return (return_error(args[0], ": Permission denied\n", 126));
	}
	else if (!ft_strncmp(args[0], "./", 2) || args[0][0] == '/')
		return (return_error(args[0], ": No such file or directory\n", 127));
	return (return_error(args[0], " : command not found\n", 127));
}
