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

extern t_instruct	*first_instruct;

int	work_command(void)
{
	int		i;
	int		out;
	pid_t	pid;
	int		status;

	out = 1;
	i = -1;
	while (++i <= EXIT_CMD)
		if (first_instruct->instruc && !ft_strncmp(first_instruct->instruc, first_instruct->header->cmd_list[i], 0, ft_strlen(first_instruct->instruc)))
		{
			out = ((int (*)(t_instruct *)) \
				((void **)first_instruct->header->functions_ptr)[i])(first_instruct);
			return (out);
		}
	if (is_char_in_str(first_instruct->instruc, '='))
	{
		out = cmd_setenv(first_instruct);
		return (out); 
	}
	pid = fork();
	if (pid == -1)
	{
		printf("error creating the pid\n");
		return (-1);
	}
	else if (pid == 0)
		out = cmd_exec(first_instruct);
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
