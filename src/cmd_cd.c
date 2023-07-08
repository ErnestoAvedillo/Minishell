/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 17:31:29 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_cd(char **str)
{
	char *dir;

	dir = (char *) malloc(1024 * sizeof(char));
	dir [0] = '\0';
	if(str[1] == NULL || is_oper(str[1]))
		ft_strlcpy(dir, getenv("HOME"), 1024);
	else if (str[1][0] == '~')
	{
		ft_strlcat(dir,getenv("HOME"), 1024);
		ft_strlcat(dir,ft_substr(str[1],0,ft_strlen(str[1])),1024);
	}
	else
		ft_strlcat(dir,ft_substr(str[1],1,ft_strlen(str[1])),1024);
	if ((str[2] != NULL && !is_oper(str[2])) || chdir(dir) == -1)
		printf("bash: cd: %s: No such file or directory .\n", dir);
	else
		printf("Cambiando al dirrectorio %s - con  %s\n", getenv("PWD"), dir);
	free(dir);
	return (1);
}
