/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:10:29 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/05 19:10:31 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_cd(t_data *data)
{
	char **splited_cmd;

	splited_cmd = ft_split(data->command, ' ');
	if (chdir(splited_cmd[1]) == -1)
		printf("bash: cd: %s: No such file or directory .\n", splited_cmd[1]);
	else
		printf("Cambiando al dirrectorio %s - con  %s\n", getenv("PWD"), splited_cmd[1]);

	free_arrchar(splited_cmd);

	return (1);
}
