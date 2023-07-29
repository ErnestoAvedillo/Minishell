/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:46:18 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/11 22:46:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	move_2_next_sing_quote(char *str, int pos)
{
	int	i;

	i = pos;
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	i++;
	return (i);
}

static char	*get_var_name(char *str, int pos)
{
	int	i;

	i = pos;
	while (str[i] && (str[i] != ' ' && str[i] != '\"'))
		i++;
	return (ft_substr(str, pos + 1, i - pos - 1));
}

static char	*replace_command(char *str, char *variable, char *value, int pos)
{
	int		j;
	char	*out;

	j = (int)(ft_strlen(str) - ft_strlen(variable) + ft_strlen(value));
	out = (char *) malloc(j * sizeof(char));
	out[j - 1] = '\0';
	j = -1;
	while (out[++j])
	{
		if (j < pos)
			out[j] = str[j];
		else if (j > pos + (int)ft_strlen(value) - 1)
			out[j] = str[j + (int)(ft_strlen(variable) - ft_strlen(value) + 1)];
		else if (value)
			out[j] = value[j - pos];
	}
	printf(" el comando es %s-- %s\n", str, out);
	free (str);
	return (out);
}

char	*replace_env_var(char *str)
{
	int		i;
	char	*variable;
	char	*value;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			i = move_2_next_sing_quote(str, i);
		if (!str[i])
			return (str);
		if (str[i] == '$')
		{
			variable = get_var_name(str, i);
			value = getenv(variable);
			str = replace_command(str, variable, value, i);
			free(variable);
			i += ft_strlen(value) - 1;
		}
	}
	return (str);
}
