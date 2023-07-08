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

int cmd_unset(char **str)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (unsetenv(str[i]) == 0)
			printf("Variable unseted succesfully %s\n", str[i]);
		else
			printf("error unseting the variale %s\n", str[i]);
		}
	free(str);
	return (1);    
}
