/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:29:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 18:01:25 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	This variable MUST be created bacause remains updated during the execution
*	of the program. If we use the variable env of the main:
*		int main (int av, char **ac, char **env)
*	in this case the variable env does not remains updated.
*/
extern char** environ;

int main (int av, char **ac)
{
	int		val;
	t_data	*data;

	data = init_vars(environ);
	while (1)
	{
		data->command = readline("enter a command Minishell> ");
		add_history(data->command);
		data->splited_cmd = ft_split(data->command, ' ');
		val = work_command(data);
		if (val == 0)
			printf("Command not found.\n");
		else if (val == -1)
			break ;
		free(data->command);
	}
	free_vars(data);
	printf("Goodbye!\n");
	return (0);
	(void) av;
	(void) ac;
}