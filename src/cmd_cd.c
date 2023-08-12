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
	int		len_dir;

	dir = (char *) malloc(1024 * sizeof(char));
	dir [0] = '\0';
	if (instruct->arg[1] == NULL)
		ft_strlcpy(dir, getenv("HOME"), 1024);
	else
	{
		len_dir = ft_strlen(instruct->arg[1]);
		if (instruct->arg[1][0] == '~')
		{
			ft_strlcat(dir, getenv("HOME"), 1024);
			ft_strlcat(dir, ft_substr(instruct->arg[1], 1, len_dir), 1024);
		}
		else
			ft_strlcat(dir, ft_substr(instruct->arg[1], 0, len_dir), 1024);
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
	char	*dir;
	char	*olddir;
	char	buffer[1024];

	dir = get_address(instruct);
	if (chdir(dir) == -1)
	{
		print_err("Minishell: cd: %s: No such file or directory .\n", dir);
		free(dir);
		return (1);
	}
	else
	{
		free(dir);
		olddir = getenv("PWD");
		setenv("OLDPWD", olddir, 1);
		dir = getcwd(buffer, sizeof(buffer));
		setenv("PWD", dir, 1);
		dir = concat_env("PWD");
		actualize_env(instruct->header->env, dir, 1);
		olddir = concat_env("OLDPWD");
		actualize_env(instruct->header->env, olddir, 1);
	}
	return (0);
}
