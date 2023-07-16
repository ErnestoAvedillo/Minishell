/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actualize_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:44:52 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/16 15:44:56 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *
 * Description:		Actualizes the array of the environment variable.
 *
 * Arguments:		char **env: Pointer to teh env variable
 *					variable to be added or removed
 *					int i : 0 indicating to remove
 *							1 indicating to add or modify
 * Returns:			NONE.
 **/
char	**actualize_env(char **env, char *str, int k)
{
	int		i;
	char	**out;

	i = -1;
	out = NULL;
	while (env[++i])
	{
		if(!ft_strncmp(env[i],str,0,ft_strlen(str)))
			break ;
	}
	if(k)
	{
		if (i < ft_len_str_arr(env))
		{
			free (env[i]);
			env[i] = str;
			return (env);
		}
		else 
			out = ft_str_arr_add(env, str);
	}
	//	else
	//		out = ft_str_arr_rem(env, i);

	if (!out)
		printf("Error allocating a new env variable.\n");
	return (out);
}
