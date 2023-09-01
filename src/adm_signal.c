/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adm_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:26:39 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/22 17:26:44 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_data	*g_header;

void	hndl_ctrl_c(int signal)
{
	(void)signal;
	if (g_header->pid != 0)
	{
		g_header->out_status = 130;
	}
	else
		g_header->out_status = 1;
	rl_on_new_line();
}

void	hndl_ctrl_d(int signal)
{
	(void)signal;
	g_header->out_status = 0;
	rl_on_new_line();
}

void	hndl_ctrl_barra(int signal)
{
	(void)signal;
	g_header->out_status = 131;
	rl_on_new_line();
}

int	add_signals(t_data *header)
{
	if (tcgetattr(STDIN_FILENO, &header->term) == -1)
		return (-1);
	header->term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &header->term);
	signal(SIGINT, hndl_ctrl_c);
	signal(SIGTERM, hndl_ctrl_d);
	signal(SIGQUIT, hndl_ctrl_barra);
	return (0);
}
