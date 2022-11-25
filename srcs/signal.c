/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:11:59 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/04 14:02:01 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(int sig)
{
	(void)sig;
	ft_putchar_fd(1, '\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	signal_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}

int	handle_signal(void)
{
	if (signal(SIGINT, signal_ctrl_c) == SIG_ERR)
		return (ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ERROR);
	return (SUCCESS);
}

void	sig_ignore(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		ft_putstr_fd(1, "\n");
}

int	disable_signal(int pid)
{
	if (pid == 0)
	{
		if (signal(SIGINT, SIG_DFL) < 0)
			return (0);
		if (signal(SIGQUIT, SIG_DFL) < 0)
			return (0);
	}
	else
	{
		if (signal(SIGINT, sig_ignore) < 0)
			return (0);
		if (signal(SIGQUIT, sig_ignore) < 0)
			return (0);
	}
	return (1);
}
