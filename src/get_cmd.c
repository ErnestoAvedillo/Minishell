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
	while (1)
	{
		if (isatty(fileno(stdin)))
			data->command = readline("Enter a command Minishell>");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			data->command = ft_strtrim(line, "\n");
			free(line);
		}
		if (!data->command)
			return;
/*				while (!data->command || data->command[0] == 0)
					data->command = readline("Enter a command Minishell>");
*/		
		add_history(data->command);
		if (check_cmd_line(data))
		{
			g_first_instruct = tokenize(data);
			if (!g_first_instruct)
				print_err("Memory alloc. error\n");
			else
				adm_redirections();
			free_inst();
			if (data->exit)
				break ;
		}
	}
}
