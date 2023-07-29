/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:37 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:38 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	work_command(t_instruct *instr)
{
	int	i;
	int	j;
	int	leninst;

	i = -1;
	leninst = ft_strlen(instr->instruc);
	while (++i <= EXIT_CMD)
	{
		j = ft_strncmp(instr->instruc, instr->header->cmd_list[i], 0, leninst);
		if (instr->instruc && !j)
		{
			instr->header->out_status = ((int (*)(t_instruct *)) \
				((void **)instr->header->functions_ptr)[i])(instr);
			exit(0);
		}
	}
	if (is_char_in_str(instr->instruc, '='))
		instr->header->out_status = cmd_setenv(instr);
	else
		instr->header->out_status = cmd_exec(instr);
	exit(0);
}
