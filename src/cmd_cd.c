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

int cmd_cd(t_instruct *intruction)
{
	char	*dir;
	int		len_dir;
	char	buffer[1024];

	dir = (char *) malloc(1024 * sizeof(char));
	dir [0] = '\0';
	if (intruction->arg != NULL && intruction->arg[0] != NULL)
		len_dir =ft_strlen(intruction->arg[0]);
	if(!intruction->arg || intruction->arg[0] == NULL )
		ft_strlcpy(dir, getenv("HOME"), 1024);
	else if (intruction->arg[0][0] == '~')
	{
		ft_strlcat(dir,getenv("HOME"), 1024);
		ft_strlcat(dir,ft_substr(intruction->arg[0],1,len_dir),1024);
	}
	else
		ft_strlcat(dir,ft_substr(intruction->arg[0],0,len_dir),1024);
	if (chdir(dir) == -1)
	{
		printf("bash: cd: %s: No such file or directory .\n", dir);
		free(dir);	
	}
	else
	{
		printf("Cambiando al dirrectorio %s - con  %s\n", getenv("PWD"), dir);
		free(dir);
		dir = getcwd(buffer, sizeof(buffer));
		setenv("PWD", dir, 1);
	}
	return (1);
}
