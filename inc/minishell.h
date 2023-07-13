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

#ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H
# include   "../libft/libft.h"
# include	<stdio.h>
# include	<stdlib.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include   <stdbool.h>
# include   <unistd.h>

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

typedef struct s_data
{
    char        *command;
    char        **splited_cmd;
    char        **env;
    char        **cmd_list;
    char        **oper_list;
    void        **functions_ptr;
} t_data;

typedef struct s_instruct
{
    char    *pre_oper;
    char    *post_oper;
    char    *instruc;
	char	**arg;
	t_data	*header;
    void    *next;
    void    *prev;
} t_instruct;

//init_vars
t_data		*init_vars(char **env);
t_instruct	*init_instructions(t_data *data);

//freevars
void		free_vars(t_data *data);
void		free_arrchar(char **arrchr);
void        free_inst(t_instruct *first_instruction);

int         cmd_echo(t_instruct *intruction);
int			cmd_cd(t_instruct *intruction);
int			cmd_env(t_instruct *intruction);
int			cmd_exit(t_instruct *intruction);
int			cmd_export(t_instruct *intruction);
int			cmd_pwd(t_instruct *intruction);
int			cmd_unset(t_instruct *intruction);
int			cmd_setenv(t_instruct *intruction);

int			work_command(t_instruct *first_inst);

//check_cmd_line
int			check_cmd_line(t_data *data);
//check_quotes
bool		quotes_ok(char *str);
//token_utils
void		fill_instruct(t_instruct *inst, char *str, int start, int end);

//tokenize
t_instruct	*tokenize(t_data *data);

//utils
char		*get_env_value(char *name_env, char **env);
char		*get_env_name(char *str);
bool		is_char_in_str(char *str, char c);
bool		is_oper(char *str);

//print_var
void        print_inst(t_instruct *intruction);

//replace_env_var
char *replace_env_var(char *str);

# endif
