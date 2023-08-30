/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:49:50 by frmurcia          #+#    #+#             */
/*   Updated: 2023/08/30 17:18:36 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	first_pipe(char *text)
{
	if (text[0] == '|')
	{
		if (text[1] && text[1] == '|')
		{
			printf("Minishell: syntax error near unexpected token `||'\n");
			data->out_status = 258;
		}
		else
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			data->out_status = 258;
		}
		return (true);
	}
	return (false);
}

int	check_two_pipes(char *text)
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
			data->out_status = 258;
			free (two_pipes);
			return (0);
		}
		else
			i++;
	}
	return (0);
}

int	new_line(void)
{
	printf("Minishell: syntax error near unexpected token `newline'\n");
	data->out_status = 258;
	return (0);
}
