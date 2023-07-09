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

int cmd_echo(t_instruct *intruction)
{
	int i;

	i = -1;
	while (intruction->arg[++i])
	{
		printf ("%s",intruction->arg[i]);
		if (intruction->arg[i + 1])
			printf(" ");
	}
	printf ("\n");
	return (1);
}
