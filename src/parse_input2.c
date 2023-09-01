/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:49:50 by frmurcia          #+#    #+#             */
/*   Updated: 2023/09/01 19:25:40 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	first_pipe(char *text)
{
	if (text[0] == '|')
	{
		if (text[1] && text[1] == '|')
			printf("Minishell: syntax error near unexpected token `||'\n");
		else
			printf("Minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	else if (text[0] == '.' && text[1] == '\0')
	{
		printf("Minishell: .: filename argument required \n");
		printf(".: usage: . filename [arguments]\n");
		return (true);
	}
	return (false);
}

bool	check_two_pipes(char *text)
{
	int		i;
	char	*two_pipes;

	i = 0;
	while (text[i])
	{
		if ((text[i] && text[i - 1] && text[i - 2]) && (text[i] == '|'
				&& text[i - 1] == ' ' && text[i - 2] == '|'))
		{
			two_pipes = (char *)malloc(sizeof(char) * 2);
			two_pipes[0] = '|';
			two_pipes[1] = '\0';
			printf("Minishell: syntax error near unexpected token: `|'\n");
			free (two_pipes);
			return (true);
		}
		else
			i++;
	}
	return (false);
}

int	new_line(void)
{
	printf("Minishell: syntax error near unexpected token `newline'\n");
	return (1);
}
