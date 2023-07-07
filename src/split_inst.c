/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:17:22 by frmurcia          #+#    #+#             */
/*   Updated: 2023/07/07 18:21:50 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_instruct  *split_inst(char *str)
{
    t_instruct *pepito;

    pepito = malloc (sizeof (t_instruct));

    printf("%s", str);

    return (pepito);
}
