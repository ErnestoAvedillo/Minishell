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

void input_file_redir(t_data *header)
{
	if (header->in_fd_type == 1)
		header->in_fd = open(header->in_fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (header->in_fd_type == 2)
		header->in_fd = open(header->in_fd_name, O_WRONLY | O_CREAT, 0666);
}

void output_file_redir(t_data *header)
{
	if (header->out_fd_type == 1)
		header->out_fd = open(header->out_fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (header->out_fd_type == 2)
		header->out_fd = open(header->out_fd_name, O_WRONLY | O_CREAT, 0666);
}

void adm_file_redir(t_data *header)
{
	input_file_redir(header);
	output_file_redir(header);
	if (header->out_fd_type)
	{
		dup2(header->out_fd, 1);
		close(header->out_fd);
	}
}

void close_file_redir(t_data *header)
{
	if (header->in_fd_type)
		close(header->in_fd);
	dup2(1, 1);
	close(1);
//	if (header->out_fd_type)
//		close(header->out_fd);

}