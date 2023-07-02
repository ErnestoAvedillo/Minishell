/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:18:39 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:18:47 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    set_func_list(t_data *data)
{
    data->functions_ptr = (void**) malloc ((EXIT_CMD + 1) * sizeof(void*));
    data->functions_ptr[ECHO_CMD] = &cmd_echo;
    data->functions_ptr[PWD_CMD] = &cmd_pwd;
    data->functions_ptr[EXPORT_CMD] = &cmd_export;
    data->functions_ptr[UNSET_CMD] = cmd_unset;
    data->functions_ptr[ENV_CMD] = cmd_env;
    data->functions_ptr[EXIT_CMD] = cmd_exit;
    data->functions_ptr[EXIT_CMD] = NULL;
}

t_data  *init_vars(char **env)
{
    t_data *data;

    data =  (t_data *) malloc (sizeof (t_data));
    data->cmd_list = ft_split(COMMANDS, ' ');
    data->env = env;
    set_func_list(data);
    return (data);
}
