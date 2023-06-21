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

//int main (int av, char **ac);
int	main()
{
	char *line;
	while (1)
	{
		printf("Enter a line of text: ");
		line = readline("Minishell> ");
		add_history(line);
		printf("You entered: %s\n", line);
	}
	free(line);
	return (0);
}