/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:29:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 18:01:25 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_inst(t_instruct *intruction)
{
	t_instruct	*inst;
	int 		i;

	inst = intruction;
	while (inst)
	{
		printf ("pre_oper %s\n", inst->pre_oper);
		printf ("post_oper %s\n", inst->post_oper);
		printf ("comando %s\n", inst->instruc);
		i = 0;
		if (inst->arg != NULL)
			while(inst->arg[i])
			{
				printf (" argumento %i, vale %s\n", i , inst->arg[i]);
				i++;
			}
		inst = inst->next;
	}
}
