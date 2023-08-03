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

static void	exec_ext_cmd(t_instruct *instr)
{
	instr->pid = fork();
	if (instr->pid == -1)
	{
		printf("fork error\n");
		return ;
	}
	else if (instr->pid == 0)
		cmd_exec(instr);
	instr->header->out_status = 1;
	wait(NULL);
}

void	work_1_command(t_instruct *instr)
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
			return;
		}
	}
	if (is_char_in_str(instr->instruc, '='))
		instr->header->out_status = cmd_setenv(instr);
	else
		exec_ext_cmd(instr);
	return ;
}

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
			((int (*)(t_instruct *)) \
					((void **)instr->header->functions_ptr)[i])(instr);
			exit(0);
		}
	}
	if (is_char_in_str(instr->instruc, '='))
		cmd_setenv(instr);
	else
		cmd_exec(instr);
	exit(0);
}
