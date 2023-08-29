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
 * Description:		Infinite while function with a readline to introduce a command
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

//		while (!data->command || data->command[0] == 0)
//			data->command = readline("Enter a command Minishell>");
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
		else
		{
			free(data->command);
			data->command = NULL;
		}
	}
}
