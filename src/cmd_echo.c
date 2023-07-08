/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:59:18 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 19:59:25 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_echo(char **str)
{
	int i;

	i = 0;
	while (str[++i] && !is_oper(str[i]))
	{
		printf ("%s",str[i]);
		if (str[i + 1] && !is_oper(str[i + 1]))
			printf(" ");
	}
	printf ("\n");
	return (1);
}
