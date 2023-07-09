/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:36 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:39 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_setenv(t_instruct *intruction)
{
	int		i;

	i = -1;
	while (intruction->arg[++i])
	{
		if(!is_char_in_str(intruction->arg[i],'='))
			return (1);
		if (setenv(intruction->arg[i], intruction->arg[i + 1], 1) == 0)
		{
			printf ("Variable %s set succesfully with %s\n", intruction->arg[i], intruction->arg[i + 1]);
		}
		else
		{
			printf ("Variable %s failed to set with %s\n", intruction->arg[i], intruction->arg[i + 1]);
		}
		i += 2;
	}
	return (1);
}
