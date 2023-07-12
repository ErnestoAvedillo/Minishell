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

char	*replace_env_var(t_instruct *inst, char *str)
{
	int 	i;
	int 	j;
	char 	*variable;
	char 	*value;
	char 	*out;

	while (str[++i])
	{
		if (str[i] == "\'")
			while (str[i] != "\'")
				i++;
		if (str[i] == '$')
		{
			j = i;
			while (str[j] != ' ')
				j++;
			variable = ft_subst_str(str, i + 1, j);
			value = getenv(variable);
			j = (ft_strlen(str) - ft_strle(variable) + ft_strlen(value) + 1);
			out = (char *)malloc(j *sizeof(char));
			out[j] = '\0';
			j = 0
			while (out[j])
			{
				if (j < i || j > i + ft_strlen(value))
					out[j] = str[j];
				else
					out[j] = value[j - i];
			}
			free(str);
			str = out;
			out = NULL;
			i += ft_strlen(value);
		}
	}
	return (str);
}