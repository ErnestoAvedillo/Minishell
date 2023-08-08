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
	char	*aux;
	int		end;
	int		pos;

	pos = 0;
	aux = ft_strdup(instr->header->command);
	if (aux[start] == '>' && aux[start + 1] == '>')
		instr->header->out_fd_type = 2;
	else
		instr->header->out_fd_type = 1;
	pos += instr->header->out_fd_type;
	while (aux[start + pos] == ' ')
		pos++;
	end = pos;
	while (aux[start + end] && aux[start + end] != ' ' \
			&& aux[start + end] != '|')
		end++;
	instr->header->out_fd_name = ft_substr(aux, start + pos, end);
	free(aux);
	out = ft_strdup(instr->header->command);
	out[start] = '\0';
	aux = out + end;
	//ft_strlcat(out, ft_substr(out, end, ft_strlen(out)), ft_strlen(out));
	ft_strlcat(out, aux, ft_strlen(out));
	free(instr->header->command);
	instr->header->command = out;
}

void	ext_in_file(t_instruct *instr, int start)
{
	char	*out;
	char	*aux;
	int		end;
	int		pos;

	pos = 0;
	aux = ft_strdup(instr->header->command);
	if (aux[start] == '<' && aux[start + 1] == '<')
		instr->header->in_fd_type = 2;
	else
		instr->header->in_fd_type = 1;
	pos += instr->header->in_fd_type;
	while (aux[start + pos] == ' ')
		pos++;
	end = pos;
	while (aux[start + end] && aux[start + end] != ' ' \
			&& aux[start + end] != '|')
		end++;
	instr->header->in_fd_name = ft_substr(aux, start + pos, end - pos);
	out = ft_strdup(instr->header->command);
	out[start] = '\0';
	aux = out + start + end;
	ft_strlcat(out, aux, ft_strlen(instr->header->command));
	free(instr->header->command);
	instr->header->command = out;
}

size_t	check_is_redir(char *str, char c)
{
	int		pos;
	bool	quot[2];

	pos = -1;
	quot[1] = false;
	quot[0] = false;
	while (str[++pos])
	{
		if(str[pos] == '\'')
			quot[0] = !quot[0];
		if(str[pos] == '\"')
			quot[1] = !quot[1];
		if(str[pos] == c && !quot[0] && !quot[1])
			return (pos);
	}
	return (0);
}

void	check_ext_files(t_instruct *instr)
{
	char	*out;
	size_t		pos;

	out = ft_strdup(instr->header->command);
	pos = check_is_redir(out, '>');
	if (pos != 0 && pos < ft_strlen(out))
		ext_out_file(instr, (int)pos);
	free(out);
	out = ft_strdup(instr->header->command);
	pos = check_is_redir(out, '<');
	if (pos != 0 && pos < ft_strlen(out))
		ext_in_file(instr, (int)pos);
	free(out);
}

void ft_strrmchr(char *str, int n)
{
	int i;
	int str_len;

	str_len = ft_strlen(str);
	i = -1;
	while (++i < str_len)
	{
		if(i >= n)
			str[i] = str[i + 1];
	}
}