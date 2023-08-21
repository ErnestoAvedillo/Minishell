/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_position_zero.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:39:13 by frmurcia          #+#    #+#             */
/*   Updated: 2023/08/21 16:39:17 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
​bool is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (true);
	return (false);
}

bool is_redir(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

​char *free_spaces(char *data)
{
    int i = 0;
    int o = 0;
    char *free_spaces = malloc(sizeof(char) * (ft_strlen(data) + 1));
 if (free_spaces == NULL)
        return NULL;
    while (data[i])
    {
        if (data[i] == ' ' || data[i] == '\t')
        {
            while (data[i] == ' ' || data[i] == '\t')
                i++;
        }
        else
        {
            if (o > 0 && (data[i - 1] == ' ' || data[i - 1] == '\t'))
                free_spaces[o++] = ' ';
            free_spaces[o++] = data[i++];
        }
    }
    free_spaces[o] = '\0';
    return (free_spaces);
}

char    *free_quotes(char *data)
{
	char    *f_spaces;
	int     i;
	int     o;
	char    quot;

	f_spaces = free_spaces(data);
	i = 0;
	o = 0;
	char *free_quotes = malloc(sizeof(char) * (ft_strlen(f_spaces)) + 1);
	if (free_quotes == NULL)
		return (NULL);
	while (f_spaces[i])
	{
		if (is_quote(f_spaces[i]))
		{
			quot = f_spaces[i];
			i++;
			while (f_spaces[i] != quot)
				i++;
			free_quotes[o] = 0xff;
			i++;
			o++;
		}
		else
			free_quotes[o++] = f_spaces[i++];
	}
	free_quotes[o] = '\0';
	free(f_spaces);
	return (free_quotes);
}

int	is_newline(char *str)
{
	char	*red;
	int		i;

	i = 0;
	red = free_quotes(str);
	if (is_redir(red[0]))
	{
		if (ft_strlen(red) == 2 && is_redir(red[1]) && red[0] == '>' && red[1] == '<')
		{
			print_err("Minishell: syntax error near unexpected token '<'\n");
			data->out_status = 258;
			return (0);
		}
		if ((ft_strlen(red) == 1) || (ft_strlen(red) == 2 && is_redir(red[1])) ||
			  (ft_strlen(red) == 3 && is_redir(red[1]) && is_redir(red[2]) &&
			  red[0] == '<' && red[1] == '<' && red[2] == '<'))
		{
			print_err("Minishell: syntax error near unexpected token `newline'\n");
/			data->out_status = 258;
			return (0);
		}
	}
	return (0);
}