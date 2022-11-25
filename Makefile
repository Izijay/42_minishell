# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 13:28:01 by mdupuis           #+#    #+#              #
#    Updated: 2022/05/13 17:19:56 by ranuytte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors:
########################
BOLD = \033[1m
BLUE = \033[0;34m
CYAN = \033[36m
GREEN = \033[32m
ORANGE = \033[93m
PURPLE = \033[0;95m
RED = \033[0;91m
END = \033[0m
########################

NAME	        =		minishell

						
SRCS            =		srcs/main.c\
						srcs/env.c\
						srcs/signal.c\
						srcs/utils/env_utils.c\
						srcs/utils/error_and_status.c\
						srcs/calls/call_env.c\
						srcs/calls/call_exit.c\
						srcs/calls/select_call.c\
						srcs/calls/call_export.c\
						srcs/calls/call_export_utils.c\
						srcs/calls/call_unset.c\
						srcs/calls/call_cd.c\
						srcs/calls/call_pwd.c\
						srcs/utils/env_utils_2.c\
						srcs/calls/call_echo.c\
						srcs/meta_char/meta_central.c\
						srcs/meta_char/dollar.c\
						srcs/meta_char/quotes.c\
						srcs/meta_char/dbl_quotes.c\
						srcs/utils/meta_utils.c\
						srcs/redirection/main_redirection.c\
						srcs/redirection/redir_heredoc.c\
						srcs/redirection/init_and_set_redirection.c\
						srcs/redirection/redirection_utils.c\
						srcs/redirection/init_redirection_utils.c\
						srcs/meta_char/quotes_finder.c\
						srcs/meta_char/init_g.c\
						srcs/redirection/redirection_utils_helper.c\
						srcs/calls/perror_help.c\
						srcs/utils/handle_signal.c

INCLUDES_DIR     =       includes/

LIB_DIR         =       libft/

LIBFT           =       libft/libft.a

CC              =       clang

OBJS            =       ${SRCS:.c=.o}

RM          =       rm -rf

FLAGS       =       -Wall -Werror -Wextra -g

HEADER		=		includes/minishell.h

.c.o:		
						@${CC} ${FLAGS} -I${INCLUDES_DIR} -c $< -o ${<:.c=.o}
						@echo "\t\t${BOLD}${GREEN}[[LOADED]]${END} ${PURPLE}${<:.s=.o}${END}"

all:			${NAME}

${NAME}:		  ${OBJS} ${HEADER}
						@make -C ${LIB_DIR} 2>/dev/null
						@${CC} ${FLAGS} -I${INCLUDES_DIR} -lncurses -o ${NAME} ${OBJS} ${LIBFT} -lreadline
						@echo "\t\t${BOLD}${CYAN} libft.a${END}   ${GREEN}[ OK ]${END}"
						@echo "\t\t${BOLD}${CYAN}minishell${END}   ${GREEN}[ OK ]${END}"
clean:
						@make -C ${LIB_DIR} clean
						@${RM} ${OBJS} ${OBJS_B}
						@echo "\n${BOLD}${RED}\t\t *.o files deleted.${END}"

fclean:		clean
						@make -C ${LIB_DIR} fclean
						@${RM} ${NAME} ${NAME_B}
						@echo "\t\t${BOLD}${RED}libft.a deleted.${END}"
						@echo "\t\t${BOLD}${RED}Program minishell deleted.${END}"

re:		fclean all

.PHONY:           all     clean   fclean  re
