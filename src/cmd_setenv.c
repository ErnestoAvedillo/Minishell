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

int cmd_setenv(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if(!is_char_in_str(str[i],'='))
			return (1);
		if (setenv(str[i], str[i + 1], 1) == 0)
		{
			printf ("Variable %s set succesfully with %s\n", str[i], str[i + 1]);
		}
		else
		{
			printf ("Variable %s failed to set with %s\n", str[i], str[i + 1]);
		}
		i += 2;
	}
	return (1);
}
