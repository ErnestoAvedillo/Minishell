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

int cmd_env(t_instruct *intruction)
{   
	char buffer[1024];
	char *curdir;
	char **ptr;

	if(!ft_strncmp(intruction->arg[0], "PWD", 0, 3))
	{
		curdir = getcwd(buffer, sizeof(buffer));
		printf("%s\n", curdir);
		return (1);
	}
	else
		ptr = intruction->header->env;
		while(*ptr != NULL)
		{
			printf("%s\n",*ptr);
			ptr++;
		}

	return (1);
}
