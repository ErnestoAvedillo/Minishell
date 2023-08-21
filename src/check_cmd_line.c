/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 17:31:29 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_strrmallchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			ft_strrmchr(str, i);
}

void	ft_rm_btw_quotes(char *str)
{
	int		i;
	bool	isquote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			isquote = !isquote;
		while (str[i] && isquote)
		{
			ft_strrmchr(str, i);
			if (str[i] == '\"')
				isquote = !isquote;
		}
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			isquote = !isquote;
		while (str[i] && isquote)
		{
			ft_strrmchr(str, i);
			if (str[i] == '\'')
				isquote = !isquote;
		}
	}
}

int	check_pipes(t_data *data)
{
	int	i;

	if (data->command[0] == '|')
	{
		print_err("Minishell: syntax error near unexpected token '|'\n");
		data->out_status = 258;
		return (0);
	}
	i = -1;
	while (data->command[++i])
	{
		if (data->command[i] == '|' && data->command[i + 1] != '|')
		{
			while (data->command[++i] == ' ')
				;
			if (data->command[i] == '|')
			{
				print_err("Minishell: syntax error near unexpected token '|'\n");
				data->out_status = 258;
				return (0);
			}
		}
	}
	return (1);
}

int	check_redir(t_data *data)
{
	int		i;
	bool	blank;

	blank = false;
	i = -1;
	while (data->command[++i])
	{
		if (data->command[i] == '>' || data->command[i] == '<')
		{
			if (data->command[i + 1] == '\0')
			{
				print_err("Minishell: syntax error near \
					unexpected token 'newline'\n");
				data->out_status = 258;
				return (0);
			}
			while (data->command[++i] == ' ')
				if (!blank)
					blank = !blank;
		}
		if (data->command[i] == '>' && blank)
		{
			print_err("Minishell: syntax error near unexpected token '>'\n");
			data->out_status = 258;
			return (0);
		}
		else if (data->command[i] == '<' && blank)
		{
			print_err("Minishell: syntax error near unexpected token '<'\n");
			data->out_status = 258;
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_data *data, char *errstr, int err_nr)
{
	char	**out;
	int		i;
	char	*aux;

	aux = ft_strdup(data->command);
	ft_strrmallchr(aux, ' ');
	ft_rm_btw_quotes(aux);
	out = ft_split(errstr, ' ');
	i = -1;
	while (out[++i])
	{
		if (ft_strnstr(aux, out[i], ft_strlen(aux)))
		{
			if (err_nr == 258)
				print_err("Minishell: syntax error near unexpected token %s\n", \
					out[i] + ft_strlen(out[i]) - 1);
			else if (err_nr == 127)
				print_err("Minishell: command not found.\n");
			data->out_status = err_nr;
			free_arrchar(out);
			free (aux);
			return (0);
		}
	}
	free (aux);
	free_arrchar(out);
	return (1);
}

/*
*   Checks that the command line does not have following errors
*   " = " or " =" or "= " --> is not OK
*   operands should be allways in betewwn blanks
* || !check_syntax(data,SNTX_127_ERR,127)
*/
int	check_cmd_line(t_data *data)
{
	char	*add_line;

	if (!check_pipes(data))
		return (0);
	if (!check_redir(data))
		return (0);
	if (!check_syntax(data, SNTX_258_ERR, 258))
		return (0);
	while (!quotes_ok(data->command))
	{
		add_line = readline("quotes>");
		data->command = concat_cmd(data->command, add_line);
	}
	return (1);
}
