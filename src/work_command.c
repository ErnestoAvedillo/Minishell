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

static void	back_2_screen(t_instruct *instr)
{
	if (dup2(instr->header->my_stdin, STDIN_FILENO) == -1)
		print_err("error al devolver fd in a teclado\n");
	if (dup2(instr->header->my_stdout, STDOUT_FILENO) == -1)
		print_err("error al devolver fd out a pantalla \n");
	if (dup2(instr->header->my_stderr, STDERR_FILENO) == -1)
		print_err("error al devolver fd error a pantalla \n");
}

static void	exec_ext_cmd(t_instruct *instr)
{
	int		status;
	char	*out;

	out = check_file_exists(instr);
	if (!out)
	{
		print_err("minishell: %s : command not found\n", instr->arg[0]);
		instr->header->out_status = 127;
		free(out);
		return ;
	}
	free(instr->arg[0]);
	instr->arg[0] = out;
	instr->pid = fork();
	if (instr->pid == -1)
	{
		print_err("minishell: error while forking");
		return ;
	}
	else if (instr->pid == 0)
		cmd_exec(instr);
	wait(&status);
	instr->header->out_status = WEXITSTATUS(status);
}

void	work_1_command(t_instruct *instr)
{
	int	i;
	int	j;

	i = -1;
	adm_file_redir(instr);
	if (instr->arg[0])
	{
		while (++i <= EXIT_CMD)
		{
			j = ft_strncmp(instr->arg[0], instr->header->cmd_list[i], 0, \
							ft_strlen(instr->arg[0]));
			if (instr->arg[0] && !j)
			{
				instr->header->out_status = ((int (*)(t_instruct *)) \
						((void **)instr->header->functions_ptr)[i])(instr);
				back_2_screen(instr);
				return ;
			}
		}
		if (is_char_in_str(instr->arg[0], '='))
			instr->header->out_status = cmd_setenv(instr);
		else
			exec_ext_cmd(instr);
	}
	back_2_screen(instr);
}

void	work_command(t_instruct *instr)
{
	int	i;
	int	j;
	int	leninst;

	i = -1;
	if (instr->arg[0] == NULL)
		exit(0);
	leninst = ft_strlen(instr->arg[0]);
	while (++i <= EXIT_CMD)
	{
		j = ft_strncmp(instr->arg[0], instr->header->cmd_list[i], 0, leninst);
		if (instr->arg[0] && !j)
		{
			((int (*)(t_instruct *)) \
					((void **)instr->header->functions_ptr)[i])(instr);
			exit(0);
		}
	}
	if (is_char_in_str(instr->arg[0], '='))
		cmd_setenv(instr);
	else
		cmd_exec(instr);
	exit(0);
}
