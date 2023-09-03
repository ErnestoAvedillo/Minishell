/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adm_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:26:39 by eavedill          #+#    #+#             */
/*   Updated: 2023/09/03 13:02:18 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_out_status;

/*****
 * -1 para comando bloqueante - Pone ^C y termina el proceso
 * -2 para comando bloqueante dentro de comillas... - termina el proceso
 * -3 bloqueante dentro de redireccion - Pone >, termina el proceso
 *  else el resto
 * */
void	hndl_ctrl_c(int signal)
{
	(void)signal;
/*	if (g_out_status == -1)
	{
		write (1, "^C\n", 3);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_out_status = 130;
	}
	else if (g_out_status == -3)
	{
		write (0, "\n", 1);
		g_out_status = 1;
	}
	else
	{*/
		write (1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_out_status = 1;
//	}
}

void	hndl_ctrl_slash(int signal)
{
	(void)signal;
	if (g_out_status == -1)
	{
		ft_printf("^\\Quit: 3\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		g_out_status = 131;
	}
	else
		rl_redisplay();
}

void	hndl_ctrl_slash_frk(int signal)
{
	(void)signal;
	exit(131);
}

void	hndl_ctrl_c_frk(int signal)
{
	(void)signal;
	write(1, "^C\n", 3);
	exit(130);
}

int	add_signals(t_data *header)
{
	(void) header;
	if (tcgetattr(STDIN_FILENO, &header->term) == -1)
		exit (1);
	header->term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &header->term) == -1)
		exit (1);
	if (signal(SIGINT, hndl_ctrl_c) == SIG_ERR)
		exit (1);
	if (signal(SIGQUIT, hndl_ctrl_slash) == SIG_ERR)
		exit (1);
	return (0);
}

void	han_c_fork(int signal)
{
	(void)signal;
	write (1, "\n", 1);
	exit (130);
}

void	han_c_fork2(int signal)
{
	(void)signal;
	write (1, "^C\n", 3);
	exit (130);
}

void reset_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}