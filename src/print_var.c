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

void	print_inst(t_instruct *instructions)
{
	t_instruct	*inst;
	int			i;

	inst = instructions;
	while (inst)
	{
		printf ("comando %s\n", inst->instruc);
		i = 0;
		if (inst->arg != NULL)
		{
			while (inst->arg[i])
			{
				printf (" argumento %i, vale %s\n", i, inst->arg[i]);
				i++;
			}
		}
		printf("fd 0 = %i -- fd1 = %i\n", inst->pipefd[0], inst->pipefd[1]);
		inst = inst->next;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
		++i;
	i = ft_len_str_arr(arr) - ft_min(i, 5);
	while (arr[i] != NULL)
	{
		ft_printf("%p -- %s\n", arr[i], arr[i]);
		++i;
	}
}
