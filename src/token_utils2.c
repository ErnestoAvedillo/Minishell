/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:49:26 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/24 09:49:29 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	replace_char(char c, char c1, char c2)
{
	if (c && c == (char)c1)
		return (c2);
	return (c);
}

/**
 *
 * Description:		Replace all charachtes beteween quotes.
 *
 * Arguments:		char *str The string where to replace the spaces between 
 * 					quotes.
 *
 * Returns:			NONE
 **/
void	replace_char_btw_quotes(char *str, unsigned int c1, unsigned int c2)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (j == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			j = 1;
			if (str[i] == '\"')
				j = 2;
			str[i] = ' ';
		}
		while (j != 0)
		{
			i++;
			str[i] = replace_char(str[i], c1, c2);
			if ((j == 1 && str[i] == '\'') || (j == 2 && str[i] == '\"'))
			{
				str[i] = ' ';
				j = 0;
			}
		}
	}
}

void	ext_out_file(t_instruct *instr, int start)
{
	char	*out;
	int		end;
	int		i;

	i = 0;
	out = ft_strdup(instr->header->command);
	if (out[start] == '>' && out[start + 1] == '>')
	{
		instr->header->out_fd_type = 2;
		i++;
	}
	else
		instr->header->out_fd_type = 1;
	i++;
	while (out[start + i] == ' ')
		i++;
	end = (int)(ft_strchr(out, start + i, ' ') - out);
	instr->header->out_fd_name = ft_substr(out, start + i, end);
	out = ft_substr(out, 0, start);
	ft_strlcat(out, ft_substr(out, end, ft_strlen(out)), ft_strlen(out));
	free(instr->header->command);
	instr->header->command = out;
	return ;
}

void	ext_in_file(t_instruct *instr, int start)
{
	char	*out;
	int		end;
	int		i;

	i = 0;
	out = ft_strdup(instr->header->command);
	if (out[start] == '<' && out[start + 1] == '<')
	{
		instr->header->in_fd_type = 2;
		i++;
	}
	else
		instr->header->in_fd_type = 1;
	i++;
	while (out[start + i] == ' ')
		i++;
	end = (int)(ft_strchr(out, start + i, ' ') - out);
	instr->header->in_fd_name = ft_substr(out, start + i, end);
	out = ft_substr(out, 0, start);
	ft_strlcat(out, ft_substr(out, end, ft_strlen(out)), ft_strlen(out));
	free(instr->header->command);
	instr->header->command = out;
	return ;
}

void	check_ext_files(t_instruct *instr)
{
	char	*ptr;
	char	*out;

	out = ft_strdup(instr->header->command);
	ptr = ft_strchr(out, 0, '>'); //ojo tiene que ser fuera de comillas
	if (ptr != NULL && ptr < out + ft_strlen(out))
		ext_out_file(instr, (int)(ptr - out));
	free(out);
	out = ft_strdup(instr->header->command);
	ptr = ft_strchr(out, 0, '<'); // ojo tiene que ser fuera de comillas
	if (ptr != NULL && ptr < out + ft_strlen(out))
		ext_in_file(instr, (int)(ptr - out));
	free(out);
}
