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

t_fd_struc *get_fd_in_address(t_instruct *instr)
{
	t_fd_struc *new_fd;
	t_fd_struc *cur_fd;

	new_fd = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
	new_fd->next = NULL;
	cur_fd = instr->in;
	if (cur_fd != NULL)
	{
		while (cur_fd->next)
			cur_fd = cur_fd->next;
		cur_fd->next = new_fd;
	}
	else
		instr->in = new_fd;
	return (new_fd);
}

t_fd_struc *get_fd_out_address(t_instruct *instr)
{
	t_fd_struc *new_fd;
	t_fd_struc *cur_fd;

	new_fd = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
	new_fd->next = NULL;
	cur_fd = instr->out;
	if (cur_fd != NULL)
	{
		while (cur_fd->next)
			cur_fd = cur_fd->next;
		cur_fd->next = new_fd;
	}
	else
		instr->out = new_fd;
	return (new_fd);
}

t_fd_struc *get_fd_err_address(t_instruct *instr)
{
	t_fd_struc *new_fd;
	t_fd_struc *cur_fd;

	new_fd = (t_fd_struc *)malloc(1 * sizeof(t_fd_struc));
	new_fd->next = NULL;
	cur_fd = instr->err;
	if (cur_fd != NULL)
	{
		while (cur_fd->next)
			cur_fd = cur_fd->next;
		cur_fd->next = new_fd;
	}
	else
		instr->err = new_fd;
	return (new_fd);
}
char	*ext_out_file(t_instruct *instr, int start, char *str)
{
	char	*aux;
	int		end;
	int		pos;
	t_fd_struc *new_fd;

	new_fd = get_fd_out_address(instr);
	pos = 0;
	if (str[start] == '>' && str[start + 1] == '>')
		new_fd->fd_type = 2;
	else
		new_fd->fd_type = 1;
	pos += new_fd->fd_type;
	while (str[start + pos] == ' ')
		pos++;
	end = pos;
	while (str[start + end] && str[start + end] != ' ' \
			&& str[start + end] != '>' && str[start + end] != '<' \
			&& str[start + end] != '|')
		end++;
	new_fd->fd_name = ft_substr(str, start + pos, end - pos);
	aux = ft_strrmstr(str, start, start + end);
	return (aux);
}

char *ext_err_file(t_instruct *instr, int start, char *str)
{
	char *aux;
	int end;
	int pos;
	t_fd_struc *new_fd;

	new_fd = get_fd_err_address(instr);
	pos = 0;
//	aux = ft_strdup(str);
	if (str[start] == '>' && str[start + 1] == '>')
		new_fd->fd_type = 2;
	else
		new_fd->fd_type = 1;
	pos += new_fd->fd_type;
	while (str[start + pos] == ' ')
		pos++;
	end = pos;
	while (str[start + end] && str[start + end] != ' ' && str[start + end] != '>' && str[start + end] != '<' && str[start + end] != '|')
		end++;
	new_fd->fd_name = ft_substr(str, start + pos, end - pos);
	aux = ft_strrmstr(str, start - 1, start + end);
	return (aux);
}

char	*ext_in_file(t_instruct *instr, int start, char *str)
{
	char	*aux;
	int		end;
	int		pos;
	t_fd_struc *new_fd;

	new_fd = get_fd_in_address(instr);
	pos = 0;
	if (str[start] == '<' && str[start + 1] == '<')
		new_fd->fd_type = 2;
	else
		new_fd->fd_type = 1;
	pos += new_fd->fd_type;
	while (str[start + pos] == ' ')
		pos++;
	end = pos;
	while (str[start + end] && str[start + end] != ' ' \
			&& str[start + end] != '|' && str[start + end] != '>')
		end++;
	new_fd->fd_name = ft_substr(str, start + pos, end - pos);
	aux = ft_strrmstr(str,start, start + end);
	return (aux);
}
/**
 *
 * Description:		Looks for the position of a char c excluding those which are between quotes.
 *					
 * Arguments:		char* where to look at
 *					char charachter to look for.
 * Returns:			int: >= 0 with the position of the charachterin the str
 * 							-1 if there is none.
 **/
int	check_is_redir(char *str, char c)
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
	return (-1);
}

char	*check_ext_files(t_instruct *instr, char *str)
{
	char	*out[2];
	int		pos;

	if(!str)
		return (str);
	out[0] = ft_strdup(str);
	pos = check_is_redir(out[0], '>');
	while (pos >= 0 && pos < (int)ft_strlen(out[0]))
	{
		if ((pos > 1 && out[0][pos - 1] == '2' && out[0][pos - 2] == ' ') || \
				(pos > 0 && out[0][pos - 1] == '2'))
			out[1] = ext_err_file(instr, (int)pos, out[0]);
		else
			out[1] = ext_out_file(instr, (int)pos, out[0]);
		free(out[0]);
		out[0] = out[1];
		pos = check_is_redir(out[0], '>');
	}
	pos = check_is_redir(out[0], '<');
	while (pos >= 0 && pos < (int)ft_strlen(out[0]))
	{
		out[1] = ext_in_file(instr, (int)pos, out[0]);
		free(out[0]);
		out[0] = out[1];
		pos = check_is_redir(out[0], '<');
	}
	free(str);
	return (out[0]);
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