/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:57 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:02 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_unset(t_instruct *instruct)
{
	int		i;

	i = -1;
	while (instruct->arg[++i])
	{
		if (unsetenv(instruct->arg[i]) == 0)
			printf("Variable unseted succesfully %s\n", instruct->arg[i]);
		else
			printf("error unseting the variale %s\n", instruct->arg[i]);
	}
	return (1);
}
