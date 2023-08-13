/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 17:31:29 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_pipes (t_data *data)
{
	int	i;

	if(data->command[0] == '|')
	{
		print_err("Minishell: syntax error near unexpected token '|'\n");
		data->out_status = 258;
		return (0);
	}
	i = -1;
	while(data->command[++i])
	{
		if(data->command[i] == '|' && data->command[i + 1] != '|')
		{
			while (data->command[++i] == ' ')
			;
		if(data->command[i] == '|')
			{
				print_err("Minishell: syntax error near unexpected token '|'\n");
				data->out_status = 258;
				return (0);
			}
		}
	}
	return (1);
}

int check_redir (t_data *data)
{
	int		i;
	bool	blank;
	
	blank = false;
	i = -1;
	while(data->command[++i])
	{
		if(data->command[i] == '>' || data->command[i] == '<')
		{
			while (data->command[++i] == ' ')
				if (!blank)
					blank = !blank;
		}
		if(data->command[i] == '>' && blank)
			{
				print_err("Minishell: syntax error near unexpected token '>'\n");
				data->out_status = 258;
				return (0);
			}
		else if (data->command[i] == '<' && blank)
			{
				print_err("Minishell: syntax error near unexpected token '<'\n");
				data->out_status = 258;
				return (0);
			}
	}
	return (1);
}

/*
*   Checks that the command line does not have following errors
*   " = " or " =" or "= " --> is not OK
*   operands should be allways in betewwn blanks
*
*/
int	check_cmd_line(t_data *data)
{
	char *add_line;

	if (!check_pipes(data))
		return(0);
	if (!check_redir(data))
		return(0);
	while (!quotes_ok(data->command))
	{
		add_line = readline("quotes>");
		data->command = concat_cmd(data->command, add_line);
	}
	return (1);
}
