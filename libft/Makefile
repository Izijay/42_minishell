# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 13:42:32 by mdupuis           #+#    #+#              #
#    Updated: 2022/05/11 12:02:09 by ranuytte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 				ft_atoi.c\
					ft_bzero.c\
					ft_calloc.c\
					ft_isalnum.c\
					ft_isalpha.c\
					ft_isascii.c\
					ft_isdigit.c\
					ft_isprint.c\
					ft_itoa.c\
					ft_memccpy.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_memcpy.c\
					ft_memmove.c\
					ft_memset.c\
					ft_freejoin.c\
					ft_putchar_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_putstr_fd.c\
					ft_split.c\
					ft_split_str.c\
					ft_strchr.c\
					ft_strdup.c\
					ft_strjoin.c\
					ft_strlcat.c\
					ft_strlcpy.c\
					ft_strcpy.c\
					ft_strlen.c\
					ft_strmapi.c\
					ft_strncmp.c\
					ft_strcmp.c\
					ft_strndup.c\
					ft_strnstr.c\
					ft_strrchr.c\
					ft_strtrim.c\
					ft_substr.c\
					ft_tolower.c\
					ft_tablen.c\
					ft_free_tab2d.c\
					ft_toupper.c\
					ft_splitrim.c\
					ft_free_this.c\
					ft_strcount.c\
					ft_strncount.c\
					ft_strcat.c\
					ft_free_this_tab2d.c

SRCS_BONUS = 		ft_lstnew.c\
					ft_lstadd_front.c\
					ft_lstsize.c\
					ft_lstlast.c\
					ft_lstadd_back.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					ft_lstiter.c

HEAD = 				libft.h

OBJS = 				${SRCS:.c=.o}

OBJS_BONUS = 		$(SRCS:.c=.o)\
					$(SRCS_BONUS:.c=.o)\

NAME = 				libft.a

CC = 				gcc

RM = 				rm -rf

CFLAGS = 			-Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 2>/dev/null

${NAME}: ${OBJS} ${HEAD}
		@ar -rc libft.a ${OBJS}

bonus:
	@$(CC) $(CFLAGS) $(SRCS_BONUS) -c ${<:.c=.o} 2>/dev/null
	@ar rc $(NAME) $(OBJS_BONUS)
	@ranlib $(NAME)

all:  ${NAME}

clean:
	@${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
