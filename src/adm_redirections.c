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
	while (instr)
	{
		if (pipe(instr->pipefd) == -1)
		{
			printf("pipe error\n");
			return (0);
		}
		instr = instr->next;
	}
	g_first_instruct->header->out_status = 0;
	return (1);
}

void	close_all_pipes(void)
{
	t_instruct	*instr;

	instr = g_first_instruct;
	while (instr)
	{
		close(instr->pipefd[0]);
		close(instr->pipefd[1]);
		instr = instr->next;
	}
}

void	redirect(t_instruct *cur_inst)
{
	t_instruct	*instr[2];

	instr[0] = cur_inst;
	if ((instr[0]->prev == NULL) && (instr[0]->next == NULL))
	{
		close(instr[0]->pipefd[0]);
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev == NULL) && (instr[0]->next != NULL))
	{
		close(instr[0]->pipefd[0]);
		dup2(instr[0]->pipefd[1], STDOUT_FILENO);
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev != NULL) && (instr[0]->next != NULL))
	{
		instr[1] = instr[0]->prev;
		close(instr[1]->pipefd[1]);
		close(instr[0]->pipefd[0]);
		dup2(instr[1]->pipefd[0], STDIN_FILENO);
		close(instr[1]->pipefd[0]);
		dup2(instr[0]->pipefd[1], STDOUT_FILENO);
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev != NULL) && (instr[0]->next == NULL))
	{
		instr[1] = instr[0]->prev;
		close(instr[1]->pipefd[1]);
		close(instr[0]->pipefd[0]);
		dup2(instr[1]->pipefd[0], STDIN_FILENO);
		close(instr[1]->pipefd[0]);
		close(instr[0]->pipefd[1]);
	}
}

void	close_prev_pipes(t_instruct *cur_inst)
{
	t_instruct	*instr[2];

	instr[0] = cur_inst;
	if ((instr[0]->prev == NULL) && (instr[0]->next == NULL))
	{
		close(instr[0]->pipefd[0]);
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev == NULL) && (instr[0]->next != NULL))
	{
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev != NULL) && (instr[0]->next != NULL))
	{
		instr[1] = instr[0]->prev;
		close(instr[1]->pipefd[0]);
		close(instr[0]->pipefd[1]);
	}
	else if ((instr[0]->prev != NULL) && (instr[0]->next == NULL))
	{
		instr[1] = instr[0]->prev;
		close(instr[1]->pipefd[0]);
	}
}

void	adm_redirections(void)
{
	t_instruct	*instr;

	if (leninstr(g_first_instruct) == 0 || !create_pipes())
		return ;
	instr = g_first_instruct;
	while (instr)
	{
		instr->pid = fork();
		if (instr->pid == -1)
		{
			printf("fork error\n");
			return ;
		}
		else if (instr->pid == 0)
		{
			redirect(instr);
			work_command(instr);
		}
		close_prev_pipes(instr);
		wait(NULL);
		instr = instr->next;
	}
	close_all_pipes();
	free_inst();
	return ;
}
