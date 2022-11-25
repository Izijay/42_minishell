/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdupuis <mdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:45:13 by mdupuis           #+#    #+#             */
/*   Updated: 2022/05/13 17:13:19 by ranuytte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

# define RED "\033[0;31m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[32;1m"
# define RESET "\033[0m"

# define ERROR 1
# define SUCCESS 0
# define FAILURE 1
# define WAIT 1000000
# define FOLLOWED_BY_NULL 0
# define FD_MAX 1024
# define EXIT_FAILURE 1

/*
** 					Variable globale -> status de retour pour $?
*/

extern unsigned char	g_status;

/*
** 					Structure for the linked list of the environment variables
*/

typedef struct s_in_env
{
	char			*name;
	char			*value;
	int				equal;
	struct s_in_env	*next;

}					t_in_env;

/*
**						Structure for valide pipe and redirection
*/

typedef struct s_pipe
{
	int						index;
	char					valid;
	struct s_pipe			*next;
}				t_pipe;

typedef struct s_redirection
{
	char					double_redirection;
	int						index;
	int						pipe_valid;
	char					valid;
	struct s_redirection	*next;
}				t_redirection;

/*
** 						Structure to handle any useful variable
*/

typedef struct s_env
{
	int						save_stdin;
	int						save_stdout;
	int						valid_pipe_count;
	int						valid_redirection_count;
	char					*line;
	char					*prompt;
	char					**envp;
	struct s_pipe			*pipe;
	struct s_redirection	*redirection;
	struct s_in_env			*in_env;
}					t_env;

/*
** 						Structure to normalize the command line
*/

typedef struct s_paclean
{
	int			quote;
	int			*i;
	int			j;
	char		*line;
	char		**ret;
	t_env		*env;
}			t_paclean;

typedef struct s_pabo
{
	int			i;
	char		*ret;
	char		*mine;
}				t_pabo;

/*
** 						Functions to set up and parse the envp in the struct
*/

void		init_env(char **envp, t_env *env);
void		free_all(t_env *env);
void		split_env(char *str, t_in_env *new);
t_in_env	*creat_node(void);
int			ft_env_in_len(t_env *env);
void		set_env_export(t_env *env, char *name, char *value, int equal);
char		*set_prompt(t_env *env, char *value);
int			handle_signal(void);
int			disable_signal(int pid);
void		handle_shlvl(t_env *env);
int			handle_status(int wstatus);
int			name_is_in_env(t_env *env, char *name);
int			perror_help(char *str);

/*
** 						Functions to interract with the struct env
*/

char		**env_get_new_envp(t_env *env);
void		env_change_value_by_name(t_env *env, char *name, char *value);
void		env_change_value_export(t_env *env, char *line, int equal);
void		env_delete_by_name(t_env *env, char *name);
void		env_split_line_equal(char *line, char **name, char **value);
char		*env_get_value(t_env *env, char *name);

/*
** 						Functions to call the builtins
*/

void		call_exit(t_env *env, char *line);
void		check_call(char *line, t_env *env);
void		call_env(t_env *env);
void		parse_call(t_env *env, char *line);
void		call_export(t_env *env, char **arg);
void		stdout_export_error(char *error);
void		call_unset(t_env *env, char *line);
void		call_cd(t_env *env, char **arg);
void		call_pwd(t_env *env, char **arg);
void		call_echo(t_env *env, char **arg, int fd);
int			return_error(char *cmd, char *msg, int status);
int			check_exec(char **args);
int			return_err_token(char token, int status);

/*
** 						Functions for meta caracteres
*/

int			meta_char_change(t_env *env, char **line);
int			pars_dol(t_env *env, char *line, int *i, char **ret);
int			meta_char_dollar_question(t_env *env, int *i, char **ret,
				char *line);
int			parsing_quote(char *line, int *i, char **ret);
int			parsing_dbl_quotes(t_env *env, char *line, int *i, char **ret);
void		pars_dbl_quote(char *line, int *i, char *value, char **tmp);
void		fill_ret(char **ret, char **value, char *tmp);
char		pars(char **line, char **ret, int b_dollar);
int			is_between_quote(char *str, int pos);
void		init_var_meta_char(t_pabo *g, char **line);

/*
** 						Functions to handle the redirections
*/

int			check_redirection(t_env *env, char *line);
int			redirection_here_document(t_env *env, char *line);
void		butcher_code(char *line, int *i, int *juju);
int			setup_node(t_env *env, char *line, int nbr_pipe);
int			create_pipe(t_env *env, int adress, char valid);
int			main_recu(t_env *env, char *line);
int			redirection_out(t_env *env, char *file);
int			redirection_in(t_env *env, char *file);
int			redirection_out_append(t_env *env, char *file);
int			free_free(char **split, char *tmp);
int			put_end_on_redirection(char *line);
void		free_list_pipe_redirection(t_env *env);
void		pipe_reverse_magic(char **split, char boldu, char harry);
void		set_list_pipe_redir(t_env *env, char *line);
int			check_file_redirection(t_env *env, char *line, int pos, int i);
int			check_line(char *line, int i);
void		error_exit(t_env *env, const char *message);
int			setup_redirection(t_env *env, char *line, int f(t_env*, char*),
				t_redirection **redirection);
int			create_redirection(t_env *env, int adress, char valid, char *line);
int			check_file_redirection_helper_out(t_env *env, char **line, int *i,
				t_redirection **redirection);
int			check_file_redirection_helper_in(t_env *env, char **line, int *i,
				t_redirection **redirection);
void		test_recu(t_env *env, char **split, int pos, int in_fd);
char		*pipe_magic(t_env *env, char *line);

#endif
