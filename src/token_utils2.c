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

char	*ext_out_file(t_instruct *instr, int start, char *str)
{
	char	*out;
	char	*aux;
	int		end;
	int		pos;

	instr->out = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
	pos = 0;
	aux = ft_strdup(str);
	if (aux[start] == '>' && aux[start + 1] == '>')
		instr->out->fd_type = 2;
	else
		instr->out->fd_type = 1;
	pos += instr->out->fd_type;
	while (aux[start + pos] == ' ')
		pos++;
	end = pos;
	while (aux[start + end] && aux[start + end] != ' ' \
			&& aux[start + end] != '>' && aux[start + end] != '<' \
			&& aux[start + end] != '|')
		end++;
	instr->out->fd_name = ft_substr(aux, start + pos, end - pos);
	free(aux);
	out = ft_strrmstr(str,start, start + end);
	return (out);
}

char *ext_err_file(t_instruct *instr, int start, char *str)
{
	char *out;
	char *aux;
	int end;
	int pos;

//	if (instr->out = NULL)
		instr->out = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
//	else
//		while instr->out->next
	pos = 0;
	aux = ft_strdup(str);
	if (aux[start] == '>' && aux[start + 1] == '>')
		instr->out->fd_type = 2;
	else
		instr->out->fd_type = 1;
	pos += instr->out->fd_type;
	while (aux[start + pos] == ' ')
		pos++;
	end = pos;
	while (aux[start + end] && aux[start + end] != ' ' && aux[start + end] != '>' && aux[start + end] != '<' && aux[start + end] != '|')
		end++;
	instr->out->fd_name = ft_substr(aux, start + pos, end - pos);
	free(aux);
	out = ft_strrmstr(str, start - 1, start + end);
	return (out);
}

char	*ext_in_file(t_instruct *instr, int start, char *str)
{
	char	*out;
	int		end;
	int		pos;

	instr->in = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
	pos = 0;
	if (str[start] == '<' && str[start + 1] == '<')
		instr->in->fd_type = 2;
	else
		instr->in->fd_type = 1;
	pos += instr->in->fd_type;
	while (str[start + pos] == ' ')
		pos++;
	end = pos;
	while (str[start + end] && str[start + end] != ' ' \
			&& str[start + end] != '|' && str[start + end] != '>')
		end++;
	instr->in->fd_name = ft_substr(str, start + pos, end - pos);
	out = ft_strrmstr(str,start, start + end);
	return (out);
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

char	*check_ext_files(t_instruct *instr, char *str)
{
	char	*out;
	char	*out2;
	size_t	pos;

	if(!str)
		return (str);
	pos = check_is_redir(str, '>');
	if (pos != 0 && pos < ft_strlen(str))
		if(pos > 0 && str[pos - 1] == '2')
			out = ext_err_file(instr, (int)pos, str);
		else
			out = ext_out_file(instr, (int)pos, str);
	else
		out = ft_strdup(str);
	pos = check_is_redir(out, '<');
	if (pos != 0 && pos < ft_strlen(out))
	{
		out2 = ext_in_file(instr, (int)pos, out);
		free(str);
		free(out);
		return (out2);
	}
	free(str);
	return (out);
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