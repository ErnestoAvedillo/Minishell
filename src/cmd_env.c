/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:00:33 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:00:38 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern char** environ;

int cmd_env(char **str)
{   
	char buffer[1024];
	char *curdir;

	if(!ft_strncmp(str[1], "PWD", 3))
	{
		curdir = getcwd(buffer, sizeof(buffer));
		printf("%s\n", curdir);
		return (1);
	}
	else
		while(*str != NULL)
		{
			printf("%s\n",*str);
			str++;
		}

	return (1);
}
