/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:41:17 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 16:35:18 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_status(int wstatus)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		ret = WTERMSIG(wstatus);
		if (ret != 131)
			ret += 128;
	}
	return (ret);
}

void	butcher_code(char *line, int *i, int *juju)
{
	*juju = 0;
	if (line[*i] == '|')
		*juju += 1;
	*i += 1;
	if ((line[*i - 1] == '<' && line[*i] == '<'))
		*i += 1;
	else if (line[*i - 1] == '>' && line[*i] == '>')
		*i += 1;
	while (!ft_isprint(line[*i]) && line[*i])
		*i += 1;
}
