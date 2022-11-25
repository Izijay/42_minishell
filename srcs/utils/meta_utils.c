/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:51:25 by mdupuis           #+#    #+#             */
/*   Updated: 2022/04/14 12:52:25 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_ret(char **ret, char **value, char *tmp)
{
	if (*ret != NULL)
	{
		*value = *ret;
		*ret = tmp;
		if (*value)
			free(*value);
	}
	else
		*ret = tmp;
}
