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

extern t_instruct	*g_first_instruct;

int	create_pipes(void)
{
	t_instruct	*instr;

	instr = g_first_instruct;
	while (instr->next)
	{
		if (pipe(instr->pipefd) == -1)
		{
			//printf("pipe error\n");
			return (0);
		}
		instr = instr->next;
	}
	g_first_instruct->header->out_status = 0;
	return (1);
}

void	redirect(t_instruct *cur_inst)
{
	t_instruct	*instr_pre;

	instr_pre = cur_inst->prev;
	if ((cur_inst->prev == NULL) && (cur_inst->next != NULL))
	{
		close(cur_inst->pipefd[0]);
		input_file_redir(cur_inst);
		if (cur_inst->out)
			output_file_redir(cur_inst);
		else
			dup2(cur_inst->pipefd[1], STDOUT_FILENO);
		close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next != NULL))
	{
		if(cur_inst->in)
			input_file_redir(cur_inst);
		else
			dup2(instr_pre->pipefd[0], STDIN_FILENO);
		close(cur_inst->pipefd[0]);
		close(instr_pre->pipefd[0]);
		if (cur_inst->out)
			output_file_redir(cur_inst);
		else
			dup2(cur_inst->pipefd[1], STDOUT_FILENO);
		close(cur_inst->pipefd[1]);
		close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next == NULL))
	{
		if (cur_inst->in)
			input_file_redir(cur_inst);
		else
			close(cur_inst->pipefd[0]);
		dup2(instr_pre->pipefd[0], STDIN_FILENO);
		close(instr_pre->pipefd[0]);
		close(instr_pre->pipefd[1]);
		output_file_redir(cur_inst);
	}
}

void	close_prev_pipes(t_instruct *cur_inst)
{
	t_instruct	*instr_pre;

	instr_pre = cur_inst->prev;
	if ((cur_inst->prev == NULL) && (cur_inst->next != NULL))
	{
		if(cur_inst->out)
			close(cur_inst->in->fd);
		else
			close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next != NULL))
	{
		if(cur_inst->in)
			close(cur_inst->in->fd);
		else
			close(instr_pre->pipefd[0]);
		if(cur_inst->out)
			close(cur_inst->out->fd);
		else
			close(cur_inst->pipefd[1]);
	}
	else if ((cur_inst->prev != NULL) && (cur_inst->next == NULL))
	{
		if(cur_inst->in)
			close(cur_inst->in->fd);
		else
			close(instr_pre->pipefd[0]);
		if(cur_inst->out)
			close(cur_inst->out->fd);
		close(instr_pre->pipefd[1]);
	}
}

int	check_is_1_command(void)
{
	int			leninst;

	leninst = leninstr(g_first_instruct);
	if (leninst == 0 )
		return (1);
	if(!g_first_instruct->header->command[0])
		return(1);
	if (leninst == 1)
	{
		work_1_command(g_first_instruct);
		return (1);
	}
	return (0);
}

void	adm_redirections(void)
{
	t_instruct	*instr;
	int			status;

	if (check_is_1_command())
		return;
	if (!create_pipes())
		return ;
	instr = g_first_instruct;
	while (instr)
	{
		instr->pid = fork();
		if (instr->pid == -1)
		{
			//printf("fork error\n");
			return ;
		}
		else if (instr->pid == 0)
		{
			redirect(instr);
			work_command(instr);
		}
		close_prev_pipes(instr);
		wait(&status);
		instr = instr->next;
	}
	g_first_instruct->header->out_status = WEXITSTATUS(status);
	return ;
}
