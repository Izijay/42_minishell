/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:11:26 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/11 00:16:24 by mdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
int				ft_tablen(char **tab);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strndup(const char *s1, size_t n);
int				ft_strcmp(const char *str1, const char *str2);
char			*ft_freejoin(char *s1, char *s2);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strdup(const char *src);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *str, char c);
char			**ft_split_str(char *str, char *charset);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_bzero(void *s, size_t n);
void			ft_putchar_fd(int fd, char c);
void			ft_putstr_fd(int fd, char *s);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memccpy(void *dest, const void *src, int c, size_t max);
void			*ft_memcpy(void *dest, const void *src, size_t size);
void			*ft_memchr(const void *s, int c, size_t size);
void			*ft_memset(void *str, int c, size_t count);
void			*ft_memmove(void *dst, const void *src, size_t size);
void			ft_free_tab2d(char **tab);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
char			*ft_strcpy(char *dest, char *src);
char			**ft_splitrim(const char *str, char c);
int				ft_free_this(void **ptr);
int				ft_strcount(char *str, char c);
int				ft_strncount(char *str, char c, int len);
char			*ft_strcat(char *dest, char *src);
int				ft_free_this_tab2d(char ***tab);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *nnew);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *nnew);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));

#endif
