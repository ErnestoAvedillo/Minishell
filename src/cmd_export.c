/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:13 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:15 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_export(t_data * data)
{
	char	**str;
	int		i;

	str = ft_split(data->command, ' ');
	i = 0;
	while (str[++i])
	{
		if (putenv(str[i]) == 0)
			printf("Variable exported succesfully%s\n", str[i]);
		else
			printf("error exporting the variale %s\n", str[i]);
		}
	free(str);
	return (1);
}
