/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 17:31:29 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	print_redir_nl(t_data *data)
{
	print_err("Minishell: syntax error near unexpected token 'newline'\n");
	data->out_status = 258;
	return (0);
}

static int	print_redir_tok(t_data *data, char c)
{
	print_err("Minishell: syntax error near unexpected token '%c'\n", c);
	data->out_status = 258;
	return (0);
}

int	check_redir(t_data *data)
{
	int		i;
	bool	blank;

	blank = false;
	i = -1;
	while (data->command[++i])
	{
		if (data->command[i] == '>' || data->command[i] == '<')
		{
			if (data->command[i + 1] == '\0')
				return (print_redir_nl(data));
			while (data->command[++i] == ' ')
				if (!blank)
					blank = !blank;
		}
		if ((data->command[i] == '>' || data->command[i] == '<') && blank)
			return (print_redir_tok(data, data->command[i]));
	}
	return (1);
}
