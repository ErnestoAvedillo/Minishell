/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:36 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:39 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int cmd_setenv(t_data * data)
{
    char **str;

    str = ft_split(data->command, '=');
    if (setenv(str[0], str[1], 1) == 0)
    {
        printf ("Variable %s set succesfully with %s\n", str[0], str[1]);
    } 
    else
    {
        printf ("Variable %s failed to set with %s\n", str[0], str[1]);
    }
    return (1);
    (void)data;
}
