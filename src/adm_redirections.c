/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adm_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 06:37:37 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/26 06:37:39 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_pipes(t_instruct *frst_inst)
{
	t_instruct	*instr;

	instr = frst_inst;
	while (instr->next)
	{
		if (pipe(instr->pipefd) == -1)
		{
			print_err("Pipe error\n");
			frst_inst->header->out_status = 127;
			return (0);
		}
		instr = instr->next;
	}
	frst_inst->header->out_status = 0;
	return (1);
}

void	close_prev_pipes(t_instruct *cur_inst)
{
	t_instruct	*instr_pre;

	instr_pre = cur_inst->prev;
	if ((cur_inst->prev == NULL) && (cur_inst->next != NULL))
	{
		close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next != NULL))
	{
		close(instr_pre->pipefd[0]);
		close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next == NULL))
	{
		close(instr_pre->pipefd[1]);
		close(instr_pre->pipefd[0]);
	}
}

int	check_is_1_command(t_instruct *frst_inst)
{
	int			leninst;

	leninst = leninstr(frst_inst);
	if (leninst == 0)
		return (1);
	if (!frst_inst->header->command[0])
		return (1);
	if (leninst == 1)
	{
		work_1_command(frst_inst);
		return (1);
	}
	return (0);
}

void	adm_redirections(t_instruct *frst_inst)
{
	t_instruct	*instr;
	int			status;

	if (check_is_1_command(frst_inst) || !create_pipes(frst_inst))
		return ;
	instr = frst_inst;
	while (instr)
	{
		instr->header->pid = fork();
		if (instr->header->pid == -1)
		{
			print_err("Fork error in piping\n");
			return ;
		}
		else if (instr->header->pid == 0)
		{
			redirect(instr);
			work_command(instr);
		}
		close_prev_pipes(instr);
		wait(&status);
		instr = instr->next;
	}
	frst_inst->header->out_status = WEXITSTATUS(status);
	return ;
}
