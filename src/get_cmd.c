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

t_instruct	*g_first_instruct;

/**
 *
 * Description:		Infinite while function with a readline to introduce a command
 *					
 * Arguments:		NONE
 *					
 * Returns:			NONE
 **/
void	get_cmd(t_data *data)
{
	char	*add_line;

	while (1)
	{
		while (!data->command || data->command[0] == 0)
			data->command = readline("Enter a command Minishell>");
		while (check_cmd_line(data) == 0)
		{
			add_line = readline(">");
			data->command = concat_cmd(data->command, add_line);
		}
		add_history(data->command);
		g_first_instruct = tokenize(data);
		if (!g_first_instruct)
		{
			printf("Memory alloc. error\n");
		}
		else
			adm_redirections();
		if (data->out_status == 0)
			printf("Command not found.\n");
		else if (data->out_status == -1)
			break ;
		free(data->command);
		data->command = NULL;
		free_inst();
	}
}
