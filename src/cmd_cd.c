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

/**
 *
 * Description:		creates the complete address in case ~ is given or
 * 					no argument is given 
 *					
 * Arguments:		t_instruct *instruct: structure with the instruction 
 * 					requested.
 *					
 * Returns:			char * the string with the address.
 **/
char	*get_address(t_instruct *instruct)
{
	char	*dir;

	dir = (char *) malloc(1024 * sizeof(char));
	dir [0] = '\0';
	if (instruct->arg[1] == NULL)
		ft_strlcpy(dir, getenv("HOME"), 1024);
	else
	{
		ft_strlcat(dir, instruct->arg[1], 1024);
	}
	return (dir);
}

/**
 *
 * Description:		Changes the directory 
 *					
 * Arguments:		t_instruct *instruct: structure with the instruction 
 * 					requested.
 *					
 * Returns:			1.
 **/
int	cmd_cd(t_instruct *instruct)
{
	char	*dir[2];
	char	buffer[1024];

	dir[0] = get_address(instruct);
	dir[1] = getcwd(buffer, sizeof(buffer));
	if (chdir(dir[0]) == -1)
	{
		print_err("Minishell: cd: %s: No such file or directory .\n", dir[0]);
		free(dir[0]);
		return (1);
	}
	else
	{
		free(dir[0]);
		dir[0] = getcwd(buffer, sizeof(buffer));
		setenv("OLDPWD", dir[1], 1);
		dir[0] = getcwd(buffer, sizeof(buffer));
		setenv("PWD", dir[0], 1);
		dir[0] = concat_env("PWD");
		instruct->header->env = actualize_env(instruct->header->env, dir[0], 1);
		free(dir[0]);
		dir[1] = concat_env("OLDPWD");
		instruct->header->env = actualize_env(instruct->header->env, dir[1], 1);
		free(dir[1]);
	}
	return (0);
}
