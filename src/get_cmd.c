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

t_instruct	*first_instruct;

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
	int		val;
	char	*add_line;

	while (1)
	{
		while (!data->command || data->command[0] == 0)
			data->command = readline("Enter a command Minishell>");
		while (check_cmd_line(data) == 0)
		{
			add_line = readline(">");
			val = ft_strlen(data->command) + ft_strlen(add_line) + 1;
			data->command = concat_cmd(data->command, add_line);
		}
		add_history(data->command);
		first_instruct = tokenize(data);
		if (!first_instruct)
		{
			printf("Memory alloc. error\n");
			val = 1;
		}
		else
			val = work_command();
		if (val == 0)
			printf("Command not found.\n");
		else if (val == -1)
			break ;
		free(data->command);
		data->command = NULL;
		free_inst();
	}
}
