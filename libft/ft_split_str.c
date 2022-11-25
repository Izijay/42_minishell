/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:42:50 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/06 14:50:48 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	ft_count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_is_sep(str[i + 1], charset) == 1
			&& ft_is_sep(str[i], charset) == 0)
			count++;
		i++;
	}
	return (count);
}

void	ft_strcpy_split(char *dest, char *src, char *charset)
{
	int	i;

	i = 0;
	while (ft_is_sep(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_c_count(char **tab, char *str, char *charset)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_is_sep(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_is_sep(str[i + j], charset) == 0)
				j++;
			tab[count] = (char *)malloc(sizeof(char) * (j + 1));
			if (tab[count] == NULL)
				return ;
			ft_strcpy_split(tab[count], str + i, charset);
			i = i + j;
			count++;
		}
	}
}

char	**ft_split_str(char *str, char *charset)
{
	char	**tab;
	int		count;

	count = ft_count(str, charset);
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	tab[count] = 0;
	ft_c_count(tab, str, charset);
	return (tab);
}
