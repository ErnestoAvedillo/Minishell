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
	char	**aux;

	aux = instruct->header->env;
	i = -1;
	while (instruct->arg[++i])
		if (unsetenv(instruct->arg[i]) == 0)
			instruct->header->env = actualize_env(aux, instruct->arg[i], 0);
	return (1);
}
