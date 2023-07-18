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

int    work_command(t_instruct *first_inst)
{
	int		i;
	int		out;
	pid_t	pid;
	int		status;


	out = 1;
	i = -1;
	while (++i <= EXIT_CMD)
		if (first_inst->instruc && !ft_strncmp(first_inst->instruc, first_inst->header->cmd_list[i], 0, ft_strlen(first_inst->instruc)))
		{
			out = ((int (*)(t_instruct *))((void **)first_inst->header->functions_ptr)[i])(first_inst);
			return (out);
		}
	if (is_char_in_str(first_inst->instruc, '='))
	{
		out = cmd_setenv(first_inst);
		return (out); 
	}
	pid = fork();
	if (pid == -1)
	{
		printf("error creating the pid\n");
		return (-1);
	}
	else if (pid == 0)
		out = cmd_exec(first_inst);
	// Parent process
	wait(&status); // Wait for the child process to finish

	if (WIFEXITED(status)) {
		printf("Child process completed with exit status: %d\n", WEXITSTATUS(status));
	} 
	else 
	{
		printf("Child process terminated abnormally.\n");
	}
	return (out);
}
