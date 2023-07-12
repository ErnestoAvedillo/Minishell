/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:13 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:15 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_export(t_instruct *intruction)
{
	int		i;

	i = -1;
	while (intruction->arg[++i])
	{
		if (putenv(intruction->arg[i]) == 0)
			printf("Variable exported succesfully%s\n", intruction->arg[i]);
		else
			printf("error exporting the variale %s\n", intruction->arg[i]);
		}
	return (1);
}
