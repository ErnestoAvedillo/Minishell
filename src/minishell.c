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
t_instruct *first_instruct;

int main(int av, char **ac, char **environ)
{
	int		val;
	char	*add_line;
	t_data *data;

	data = init_vars(environ);
	add_signals(data);
	while (1)
	{
		while (!data->command || data->command[0] == 0)
		{
			data->command = readline("Enter a command Minishell>");
		}
		while(check_cmd_line(data)== 0)
		{
			add_line = readline(">");
			val = ft_strlen(data->command) + ft_strlen(add_line) + 1;
			data->command = concat_cmd(data->command, add_line);
		}
		add_history(data->command);
		first_instruct = tokenize(data);
		//data->splited_cmd = ft_split(data->command, ' ');
		if (!first_instruct)
		{
			printf("Memory alloc. error\n");
			val = 1;
		}
		else
			val = work_command(first_instruct);
		if (val == 0)
			printf("Command not found.\n");
		else if (val == -1)
			break ;
		free(data->command);
		data->command = NULL;
		free_inst(first_instruct);
	}
	free_vars(data);
	printf("Goodbye!\n");
	return (0);
	(void) av;
	(void) ac;
}