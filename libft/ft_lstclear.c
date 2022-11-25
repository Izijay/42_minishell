/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:36:19 by mdupuis           #+#    #+#             */
/*   Updated: 2021/07/05 11:50:30 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*lst1;
	t_list		*lst1_next;

	if (!(*lst) || !(*del))
		return ;
	lst1 = *lst;
	while (lst1->next)
	{
		lst1 = *lst;
		(*del)(lst1->content);
		lst1_next = lst1->next;
		free(lst1);
		*lst = lst1_next;
	}
}
