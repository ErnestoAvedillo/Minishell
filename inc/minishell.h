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

//list of all accepted commands.
# define COMMANDS	"echo cd pwd export unset env exit"
# define ECHO_CMD	0
# define CD_CMD		1
# define PWD_CMD	2
# define EXPORT_CMD	3
# define UNSET_CMD	4
# define ENV_CMD	5
# define EXIT_CMD	6

# define OPERANDS	"> < >> << | $"

typedef struct s_instruct
{
    char    *pre_inst;
    char    *instruc;
    void    *next;
    void    *prev;
} t_instruct;

typedef struct s_data
{
    char        *command;
    t_instruct  *list_command;
    char        **env;
    char        **cmd_list;
    char        **oper_list;
    void        **functions_ptr;
} t_data;

//init_vars
t_data  *init_vars(char **env);
//freevars
void	free_vars(t_data *data);
void	free_arrchar(char **arrchr);

int		cmd_echo(t_data *data);
int		cmd_cd(t_data *data);
int		cmd_env(t_data *data);
int		cmd_exit(t_data * data);
int		cmd_export(t_data * data);
int		cmd_pwd(t_data * data);
int		cmd_unset(t_data * data);
int		cmd_setenv(t_data * data);

int		work_command(t_data *data);

//utils
char    *get_env_value(char *name_env, char **env);
char    *get_env_name(char *str);
int     is_char_in_str(char *str, char c);


# endif
