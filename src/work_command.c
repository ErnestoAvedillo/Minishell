/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:37 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:38 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    work_command(t_data *data)
{
	int i;
	int out;

	out = 1;
	i = -1;
	while (++i <= EXIT_CMD)
		if (!ft_strncmp(data->command, data->cmd_list[i],ft_strlen(data->command)))
		{
			out = ((int (*)(t_data *))((void **)data->functions_ptr)[i])(data);
			return (out);
		}
	return (0);
}
