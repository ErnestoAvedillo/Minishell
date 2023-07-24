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

char	*replace_env_var(char *str)
{
	int		i;
	int		j;
	char	*variable;
	char	*value;
	char	*out;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
			if (!str[i])
				return (str);
		}
		if (str[i] == '$')
		{
			j = i;
			while (str[j] && (str[j] != ' ' && str[j] != '\"'))
				j++;
			variable = ft_substr(str, i + 1, j - i - 1);
			value = getenv(variable);
			j = (int)(ft_strlen(str) - ft_strlen(variable) + ft_strlen(value));
			out = (char *) malloc(j * sizeof(char));
			out[j - 1] = '\0';
			j = -1;
			while (out[++j])
			{
				if (j < i)
					out[j] = str[j];
				else if (j > i + (int)ft_strlen(value) - 1)
					out[j] = str[j + (int)(ft_strlen(variable) - ft_strlen(value) + 1)];
				else if (value)
					out[j] = value[j - i];
			}
			free(variable);
			free(str);
			str = out;
			out = NULL;
			i += ft_strlen(value) - 1;
		}
	}
	return (str);
}
