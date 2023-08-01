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
 * Description:		removes on element of the environment if exists.
 *
 * Arguments:		char **env: Pointer to teh env variable
 *					variable to be removed
 * Returns:			char **: with the new memeoyr position of the env.
 **/
char **rem_elem_from_env(char **env, char *str)
{
	int		i;
	char	**out;

	out = env;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], str, 0, ft_strlen(str)) == 0)
		{
			out = ft_str_arr_rem(env, i);
			return(out);
		}
	}
	return (out);
}

/**
 *
 * Description:		Actualizes the array of the environment variable.
 *
 * Arguments:		char **env: Pointer to teh env variable
 *					variable to be added or removed
 *					int i : 0 indicating to remove
 *							1 indicating to add or modify
 *							2 indicating only modify if exists
 * Returns:			NONE.
 **/
char **
actualize_env(char **env, char *str, int k)
{
	int		i;
	char	**out;
	char	*aux;

	i = -1;
	out = ft_split(str, '=');
	while (env[++i])
		if (!ft_strncmp(env[i], out[0], 0, ft_strlen(out[0])))
			break ;
	free_arrchar(out);
	out = env;
	if (k == 0)
		out = rem_elem_from_env(env, str);
	else if (k != 0)
	{
		aux = strdup(str);
		if (i < ft_len_str_arr(out))
		{
			free(out[i]);
			out[i] = aux;
			return (out);
		}
		else if (k == 1)
		{
			out = ft_str_arr_add(env, aux);
		}
	}
	if (!out)
		printf("Error while allocating a new env variable.\n");
	return (out);
}
