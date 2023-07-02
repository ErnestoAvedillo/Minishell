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

char *get_env_value (char *name_env, char **env)
{
	int		len;
	char	*out;

	len = ft_strlen(name_env);
	while(*env)
	{
		if (!ft_strncmp(name_env, *env, len))
		{
			printf("%s", *env);
			break;
		}
		printf("%s", *env);
		getchar();
    }
	out = ft_strtrim (*env, name_env);
	printf("%s", out);
	return (out);
}
