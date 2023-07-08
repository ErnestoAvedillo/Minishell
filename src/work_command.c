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
	if(check_cmd_line(data)== 0)
		return (0);
	while (++i <= EXIT_CMD)
		if (!ft_strncmp(data->splited_cmd[0], data->cmd_list[i], ft_strlen(data->splited_cmd[0])))
		{
			out = ((int (*)(char **))((void **)data->functions_ptr)[i])(data->splited_cmd);
			return (out);
		}
	if (is_char_in_str(data->command, '='))
	{
		out = cmd_setenv(data->splited_cmd);
		return (out); 
	}
	return (0);
}
