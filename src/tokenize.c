/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *   Descriptinon:	Separate the commands by its operators.
 *   Arguments:		t_data *data : The structure data where the command 
 * 					and the env pointer is.
 *   Returns:		The tokenized instruction separated by the operators.
 */
t_instruct	*tokenize(t_data *data)
{
	t_instruct	*instruct[3];
	char		**subcommands;
	int			i;

	instruct[0] = init_instructions(data);
	if (instruct[0] == NULL)
		return (NULL);
	instruct[1] = instruct[0];
	subcommands = ft_split_instr(data->command, '|');
	i = -1;
	while(subcommands[++i])
	{
		//subcommands[i] = fill_instruct(instruct[1], subcommands[i]);
		subcommands[i] = fill_instruct2(instruct[1], subcommands[i]);
		if (instruct[1]->in && instruct[1]->in->fd_type == 2)
			check_delimiter(instruct[1]);
		if (subcommands[i + 1])
		{
			instruct[2] = init_instructions(data);
			instruct[1]->next = instruct[2];
			instruct[2]->prev = instruct[1];
			instruct[1] = instruct[2];
		}
	}
	free_arrchar(subcommands);
	return (instruct[0]);
}