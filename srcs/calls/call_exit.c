/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:57:08 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 17:02:51 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	atoi_special(char *str)
{
	int		i;
	int		sig;
	long	ret;

	ret = 0;
	sig = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		sig = -1;
	}
	i--;
	while (str[++i])
		ret = ret * 10 + str[i] - 48;
	ret = ret * sig;
	if (i > 19)
	{
		ret = 2;
		ft_putstr_fd(2, "Minishell: exit: ");
		ft_putstr_fd(2, str);
		ft_putstr_fd(2, ": numeric argument required\n");
	}
	return (ret);
}

int	numeric_argument(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd(2, "Minishell: exit: ");
			ft_putstr_fd(2, str);
			ft_putstr_fd(2, ": numeric argument required\n");
			return (2);
		}
		i++;
	}
	return (atoi_special(str));
}

void	call_exit(t_env *env, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	printf("exit\n");
	if (split[1] != NULL)
	{
		if (split[2] != NULL)
		{
			ft_putstr_fd(2, "Minishell: Too many arguments\n");
			g_status = 1;
			ft_free_tab2d(split);
			return ;
		}
		g_status = numeric_argument(split[1]);
		ft_free_tab2d(split);
		free(line);
		free_all(env);
	}
	free(line);
	free_all(env);
}
