/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:30:04 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/18 16:30:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H
# include   "../libft/libft.h"
# include	<stdio.h>
# include	<stdlib.h>
# include	<readline/readline.h>
# include	<readline/history.h>

//list of all accepted commands.
# define COMMANDS   "echo pwd export unset env exit"
# define ECHO_CMD   0
# define PWD_CMD    1
# define EXPORT_CMD 2
# define UNSET_CMD  3
# define ENV_CMD    4
# define EXIT_CMD   5

# define OPERANDS   "> < >> << | $"


typedef struct s_data
{
    char    *command;
    char    **env;
    char    **cmd_list; 
    void    **functions_ptr;
}   t_data;

//init_vars
t_data  *init_vars(char **env);
//freevars
void	free_vars(t_data *data);

int		cmd_echo(t_data * data);
int		cmd_env(t_data * data);
int		cmd_exit(t_data * data);
int		cmd_export(t_data * data);
int		cmd_pwd(t_data * data);
int		cmd_unset(t_data * data);

int		work_command(t_data *data);

//utils
char *get_env_value (char *name_env, char **env);


# endif
