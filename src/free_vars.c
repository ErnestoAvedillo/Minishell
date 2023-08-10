/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:27:38 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/23 20:27:40 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_instruct	*g_first_instruct;

void	free_arrchar(char **arrchr)
{
	int	i;

	if (arrchr)
	{
		i = -1;
		while (arrchr[++i])
		{
			free (arrchr[i]);
			arrchr[i] = NULL;
		}
		free(arrchr);
		arrchr = NULL;
	}
}

void	free_vars(t_data *data)
{
	free_arrchar(data->cmd_list);
	free_arrchar(data->oper_list);
	free_arrchar(data->env);
	free (data->functions_ptr);
	free (data);
	data = NULL;
}

void	free_cmd_data(t_data *data)
{
	if (data->command)
		free(data->command);
	data->command = NULL;
	if (data->in_fd_type)
	{
		free(data->in_fd_name);
		data->in_fd_name = NULL;
		data->in_fd_type = 0;
	}
	if (data->out_fd_type)
	{
		free(data->out_fd_name);
		data->out_fd_name = NULL;
		data->out_fd_type = 0;
	}
}

void free_fd_data(t_fd_struc *fd_ptr)
{
	t_fd_struc	*ptr;

	ptr = fd_ptr;
	while (ptr)
	{
		ptr->fd = 0;
		ptr->fd_type = 0;
		free(ptr->fd_name);
		fd_ptr = ptr->next;
		free(ptr);
		ptr = fd_ptr;
	}
}

void	free_inst(void)
{
	t_instruct	*instruct;

	instruct = g_first_instruct;
	free_cmd_data(instruct->header);
	while (instruct)
	{
		free(instruct->pre_oper);
		free(instruct->post_oper);
		if(instruct->instruc)
			free(instruct->instruc);
		instruct->instruc = NULL;
		free_arrchar(instruct->arg);
		free(instruct->in);
		free(instruct->out);
		g_first_instruct = instruct->next;
		free(instruct);
		instruct = g_first_instruct;
	}
}
