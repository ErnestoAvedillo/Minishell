/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:59:18 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 19:59:25 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_echo(t_instruct *instruct)
{
	int i;
	bool eol;

	i = 0;
	eol = true;
	if (ft_strncmp(instruct->arg[i],"-n",0, 2) == 0)
	{
		eol = false;
		i = 1;
	}
	while (instruct->arg[i])
	{
		printf ("%s",instruct->arg[i]);
		if (instruct->arg[i + 1])
			printf(" ");
		i++;
	}
	if (eol)
		printf ("\n");
	return (1);
}
