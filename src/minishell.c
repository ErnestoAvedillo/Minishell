/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:29:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/18 16:29:42 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main (int av, char **ac, char **env)
{
	int		val;
	char	*line;
	t_data	*data;

	data = init_vars(env);
	while (1)
	{
		printf("Enter a line of text: ");
		data->command = readline("Minishell> ");
		add_history(data->command);
		val = work_command(data);
		if (val == -1)
			printf("Command not found.\n");
	}
	free(line);
	printf("Goodbye!\n");
	return (0);
	(void) av;
	(void) ac;
}