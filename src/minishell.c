/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:29:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 18:01:25 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	This variable MUST be created bacause remains updated during the execution
*	of the program. If we use the variable env of the main:
*		int main (int av, char **ac, char **env)
*	in this case the variable env does not remains updated.
*/

int	main(int av, char **ac, char **environ)
{
	t_data	*data;
	int		out;

	data = init_vars(environ);
//	add_signals(data);
	get_cmd(data);
	out = data->out_status;
	free_vars(data);
	//printf("Goodbye!\n");
	return (out);
	(void) av;
	(void) ac;
}
