/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:36 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:39 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_pwd(t_instruct *instruct)
{
	char	buffer[1024];
	char	*curdir;

/*	if (instruct->arg[1] != NULL)
	{
		ft_printf("pwd: Too many arguments\n");
		return (1);
	}
*/	curdir = getcwd(buffer, sizeof(buffer));
	ft_printf("%s\n", curdir);
	return (0);
	(void) instruct;
}
