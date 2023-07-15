/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:09:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/15 12:09:26 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_exec(t_instruct *intruction)
{
	int	out;
	if(!intruction->arg)
		intruction->arg = (char **) malloc (1 * sizeof(char *));
	//char *command;
	printf("comando introducido %p\n",intruction->arg );
	out = execve(intruction->instruc, intruction->arg, intruction->header->env);
	free (intruction->arg);
	return (0);
}