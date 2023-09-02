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

extern int	g_out_status;

/*
*   Checks that the command line does not have following errors
*   " = " or " =" or "= " --> is not OK
*   operands should be allways in betewwn blanks
* || !check_syntax(data,SNTX_127_ERR,127)
*/
int	check_cmd_line(t_data *data)
{
	char	*add_line;

	if (!data->command)
		return (0);
	if (!check_pipes(data))
		return (0);
	if (!check_redir(data))
		return (0);
	if (!check_syntax(data))
		return (0);
	while (!quotes_ok(data->command))
	{
		g_out_status = -2;
		add_line = cmd_read("quotes>");
		data->command = concat_cmd(data->command, add_line);
	}
	return (1);
}
