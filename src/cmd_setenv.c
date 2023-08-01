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

/*
 *   Descriptinon:	Looks if there is more than one "=" in the str.
 *   Arguments:		char *s : the string to work with.
 *   Returns:		True or false.
 */
bool	more_th_1(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '=')
			j++;
	if (j > 1)
		return (true);
	return (false);
}

/*
 *   Descriptinon:	Sets the variable to the designated value.
 *   Arguments:		t_instr *instr The structure where to find  
 * 					instruction and arguments..
 *   Returns:		1 .
 */
int	cmd_setenv(t_instruct *instr)
{
	int		i;
	char	**str;
	char	*aux;

	if (more_th_1(instr->instruc))
	{
		ft_printf("Command not found.\n");
		return (1);
	}
	aux = ft_strdup(instr->instruc);
	i = -1;
	while (aux)
	{
		str = ft_split(aux, '=');
		if (setenv(str[0], str[1], 1) == 0)
			instr->header->env = actualize_env(instr->header->env, aux, 2);
		i++;
		free_arrchar(str);
		if (!instr->arg || !instr->arg[i])
			return (1);
		if (!is_char_in_str(instr->arg[i], '=') || more_th_1(instr->arg[i]))
		{
			ft_printf("Command not found.\n");
			return (1);
		}
		free(aux);
		aux = ft_strdup(instr->arg[i]);
	}
	free(aux);
	return (1);
}
