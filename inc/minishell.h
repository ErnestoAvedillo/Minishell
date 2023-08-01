/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:30:04 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 18:21:06 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
//list of all accepted commands.
# define COMMANDS	"echo cd pwd export unset env exit"
# define ECHO_CMD	0
# define CD_CMD		1
# define PWD_CMD	2
# define EXPORT_CMD	3
# define UNSET_CMD	4
# define ENV_CMD	5
# define EXIT_CMD	6

# define OPERANDS	"> < >> << | ="

# define NON_REDIR_CMD "cd export unset alias source"
# define NON_REDIR_CMD_L "ls echo printf find"

typedef struct s_data
{
	char			*command;
	char			**splited_cmd;
	char			**env;
	char			**cmd_list;
	char			**oper_list;
	void			**functions_ptr;
	int				out_status;
	struct termios	term;
}	t_data;

typedef struct s_instruct
{
	char			*pre_oper;
	char			*post_oper;
	char			*instruc;
	char			**arg;
	char			**out;
	t_data			*header;
	void			*next;
	void			*prev;
	int				signal;
	pid_t			pid;
	int				pipefd[2];
}	t_instruct;

//init_vars
t_data		*init_vars(char **env);
t_instruct	*init_instructions(t_data *data);

//freevars
void		free_vars(t_data *data);
void		free_arrchar(char **arrchr);
void		free_inst(void);

int			cmd_echo(t_instruct *instruct);
int			cmd_cd(t_instruct *instruct);
int			cmd_env(t_instruct *instruct);
int			cmd_exit(t_instruct *instruct);
int			cmd_export(t_instruct *instruct);
int			cmd_pwd(t_instruct *instruct);
int			cmd_unset(t_instruct *instruct);
int			cmd_setenv(t_instruct *instruct);
int			cmd_exec(t_instruct *instruct);
//Work_command
void 		work_command(t_instruct *instr);
void 		work_1_command(t_instruct *instr);
// check_cmd_line
int			check_cmd_line(t_data *data);
//check_quotes
bool		quotes_ok(char *str);
//token_utils
void		fill_instruct(t_instruct *inst, char *str, int start, int end);
//token_utils
void		replace_char_btw_quotes(char *str, unsigned int c1, \
									unsigned int c2);
// tokenize
t_instruct	*tokenize(t_data *data);
//utils
char		*get_env_value(char *name_env, char **env);
char		*get_env_name(char *str);
bool		is_char_in_str(char *str, char c);
bool		is_oper(char *str);
char		*concat_env(char *name_var);
// print_var
void		print_inst(t_instruct *instruct);
void		print_arr(char **arr);
// replace_env_var
char		*replace_env_var(char *str);
//actualize_env
char		**actualize_env(char **env, char *str, int k);
//adm_signals
int			add_signals(t_data *header);
//concat_cmd
char		*concat_cmd(char *str1, char *str2);
//get_cmd
void		get_cmd(t_data *data);
// ft_leninst
int			leninstr(t_instruct *list_instr);
// adm_redirections
void		adm_redirections(void);
//ft_str_arr_add
char		**ft_str_arr_add(char **arr, char *str);
//ft_str_arr_rem
char		**ft_str_arr_rem(char **arr, int pos);

#endif
