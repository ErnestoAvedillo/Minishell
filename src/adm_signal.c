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

void	hndl_ctrl_c(int signal)
{
	(void)signal;
	//printf ("^C %i\n", signal);
	exit(0);
}

void	hndl_ctrl_d(int signal)
{
	(void)signal;
	//printf (" he marcado el Ctr-d %i\n", signal);
	exit(0);
}

void	hndl_ctrl_barra(int signal)
{
	(void)signal;
	//printf (" he marcado el Ctr-\\ %i\n", signal);
	exit(0);
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
