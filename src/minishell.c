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
//extern t_instruct	*instuctions;

int main(int av, char **ac, char **environ, char ** environ)
{
	int		val;
	t_data	*data;
	t_instruct	*instuctions;

	data = init_vars(environ);
	add_signals(data);
	while (1)
	{
		data->command = readline("Enter a command Minishell>");
		printf("el comando es: %s", data->command);
		add_history(data->command);
		while(check_cmd_line(data)== 0)
			readline(">");
		instuctions = tokenize(data);
		//data->splited_cmd = ft_split(data->command, ' ');
		if (!instuctions)
		{
			printf("Memory alloc. error\n");
			val = 1;
		}
		else
			val = work_command(instuctions);
		if (val == 0)
			printf("Command not found.\n");
		else if (val == -1)
			break ;
		free(data->command);
		free_inst(instuctions);
	}
	free_vars(data);
	printf("Goodbye!\n");
	return (0);
	(void) av;
	(void) ac;
}