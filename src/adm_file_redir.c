/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adm_file_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:56:15 by eavedill          #+#    #+#             */
/*   Updated: 2023/08/04 15:56:33 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	input_file_redir(t_instruct *inst)
{
	if (!inst->in)
		return (false);
	inst->in->fd = open(inst->in->fd_name, O_RDONLY, 0666);
	printf("valor fd= %i\n",inst->in->fd);
	dup2(inst->in->fd, STDIN_FILENO);
	close(inst->in->fd);
	return (true);
}

bool	output_file_redir(t_instruct *inst)
{
	if (!inst->out)
		return (false);
	if (inst->out->fd_type == 1)
		inst->out->fd = open(inst->out->fd_name,
							 O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (inst->out->fd_type == 2)
		inst->out->fd = open(inst->out->fd_name, O_WRONLY | O_APPEND, 0666);
	printf("valor fd= %i\n",inst->out->fd);
	dup2(inst->out->fd, STDOUT_FILENO);
	close(inst->out->fd);
	return (true);
}

void	adm_file_redir(t_instruct *inst)
{
	input_file_redir(inst);
	output_file_redir(inst);
}
