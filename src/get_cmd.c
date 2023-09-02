/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:04:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/24 09:04:29 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *
 * Description:		Infinite while function with a readline(cmd_read) 
 * 						to introduce a command
 *					
 * Arguments:		NONE
 *					
 * Returns:			NONE
 **/
void	get_cmd(t_data *data)
{
	t_instruct	*frst_inst;

	while (1)
	{
		data->command = cmd_read("Enter a command Minishell>");
		add_history(data->command);
		if (check_cmd_line(data))
		{
			frst_inst = tokenize(data);
			if (!frst_inst)
				print_err("Memory alloc. error\n");
			else
				adm_redirections(frst_inst);
			free_inst(frst_inst);
			if (data->exit)
				break ;
		}
		else if (data->command == NULL)
			return ;
		else
		{
			free(data->command);
			data->command = NULL;
		}
	}
}
