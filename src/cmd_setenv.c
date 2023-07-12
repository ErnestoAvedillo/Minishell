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
bool is_more_than_1(char *str)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while(str[++i])
		if(str[i] == '=')
			j++;
	if (j > 1)
		return (true);
	return (false);
}

/*
 *   Descriptinon:	Sets the variable to the designated value.
 *   Arguments:		t_instruct *intruction The structure where to find  instruction and arguments..
 *   Returns:		1 .
 */
int cmd_setenv(t_instruct *intruction)
{
	int		i;
	char **str;

	if (is_more_than_1(intruction->instruc))
	{
		printf("Command not found.\n");
		return (1);
	}
	str = ft_split(intruction->instruc, '=');
	i = -1;
	while (str)
	{
		if (setenv(str[0], str[1], 1) == 0)
		{
			printf("Variable %s set succesfully with %s\n", str[0], str[1]);
		}
		else
		{
			printf("Variable %s failed to set with %s\n", str[0], str[1]);
		}
		i++;
		free_arrchar(str);
		if (!intruction->arg[i] || !is_char_in_str(intruction->arg[i], '='))
			return (1);
		if (is_more_than_1(intruction->arg[i]))
		{
			printf("Command not found.\n");
			return (1);
		}
		if(intruction->arg[i])
			str = ft_split(intruction->arg[i], '=');
	}
	return (1);
}
