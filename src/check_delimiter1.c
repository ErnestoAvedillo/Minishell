/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_delimiter1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:54:53 by eavedill          #+#    #+#             */
/*   Updated: 2023/08/07 19:54:56 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_start_delimit(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (str + i);
}

char	*get_end_delimit(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	aux = get_start_delimit(str);
	while (aux[i] && aux[i] != ' ' && aux[i] != '|' && aux[i] != '>')
		i++;
	return ((char *)aux + i);
}
