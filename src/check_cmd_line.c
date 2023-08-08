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
/*
*   Checks that the command line does not have following errors
*   " = " or " =" or "= " --> is not OK
*   operands should be allways in betewwn blanks
*
*/
void	check_cmd_line(t_data *data)
{
	char *add_line;

	while (!quotes_ok(data->command))
	{
		add_line = readline("quotes>");
		data->command = concat_cmd(data->command, add_line);
	}
	
}
