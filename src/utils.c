/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int get_pos ( char *str, char c)
{
    int pos;

    pos = 0;
    while (str[pos] && str[pos] != c)
        pos++;
    if (!str[pos])
        return (0);
    return (pos);
}

char *get_env_value(char *name_env, char **env)
{
	int		len;
	char	*out;

	len = ft_strlen(name_env);
	while(*env)
	{
		if (!ft_strncmp(name_env, *env, len))
		{
			break;
		}
		env++;
    }
	out = ft_strtrim (*env, name_env);
	return (out);
}

char *get_env_name(char *str)
{
	int pos;

	pos = get_pos(str, '=');
	return (ft_substr(str,0,pos));
}

int is_char_in_str(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}