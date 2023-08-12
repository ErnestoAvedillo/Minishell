/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:00:54 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:00:57 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_exit(t_instruct *inst)
{
	int	i;
	int dig;

	//printf ("Gracias por usar minishell\n");
	dig = 0;
	inst->header->exit = true;
	i = 0;
	if(inst->arg[1])
		while(inst->arg[1][i] == '-' || inst->arg[1][i] == '+')
			i++;
	while(inst->arg[1] && inst->arg[1][i])
	{
		dig = ft_isdigit(inst->arg[1][i]);
		if (!dig)
		{
			print_err("exit: %s: numeric argument required\n",inst->arg[1]);
			return (255);
		}
		i++;
	}
	if (dig)
		inst->header->out_status = ft_atoi(inst->arg[1]) % 256;
	if (inst->header->out_status < 0)
		inst->header->out_status -= 256;
	return (inst->header->out_status);
}
