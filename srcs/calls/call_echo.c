/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:47 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 18:57:39 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
		i++;
	while (arg[i] && arg[i] == 'n')
	{
		i++;
	}
	if (arg[i] != 'n' && arg[i] != '\0')
		return (1);
	return (0);
}

void	call_echo_while(char **arg, int *i, int *n)
{
	while (arg[++(*i)])
	{
		if (arg[*i][0])
		{
			if (!parse_arg(arg[*i]))
				*n = 1;
			else
				break ;
		}
	}
}

void	call_echo(t_env *env, char **arg, int fd)
{
	int		i;
	int		n;

	(void)env;
	i = 0;
	n = 0;
	if (arg[1] == NULL)
		ft_putstr_fd(fd, "\n");
	call_echo_while(arg, &i, &n);
	while (arg[i])
	{
		ft_putstr_fd(fd, arg[i]);
		if (arg[i + 1])
			ft_putchar_fd(fd, ' ');
		i++;
	}
	if (n == 0 && arg[1])
		ft_putchar_fd(fd, '\n');
	g_status = 0;
}
