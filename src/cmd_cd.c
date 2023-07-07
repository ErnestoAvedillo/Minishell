/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/07 17:31:29 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_cd(t_data *data)
{
	char **splited_cmd;

	splited_cmd = ft_split(data->command, ' ');

	if (splited_cmd[2] != NULL || chdir(splited_cmd[1]) == -1)
		printf("bash: cd: %s: No such file or directory .\n", splited_cmd[1]);
	else
		printf("Cambiando al dirrectorio %s - con  %s\n", getenv("PWD"), splited_cmd[1]);

	free_arrchar(splited_cmd);

	return (1);
}
