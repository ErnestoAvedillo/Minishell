/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:13 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:01:15 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *
 * Description:		Checks that all arguments have the proper written terminology.
 *
 *
 * Arguments:		char *str: agument given to be checked
 *
 * Returns:			Boolean variable. True is sstructure OK. False is structure NOK
 **/
bool check_args (char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if ((str[i] == '=' && str[i + 1] == ' ') || \
			(str[i] == '=' && str[i - 1] == ' '))
			return (false);
	return (true);
}

/**
 *
 * Description:		Printe the environment variables sorted
 *					
 * Arguments:		char **env
 *					
 * Returns:			NONE
 * 
 **/
void	print_env_sorted(char **env)
{
	int		i;
	char	**aux;

	aux = ft_cpy_str_arr(env);
	aux = ft_strsort_arr(aux, 1);
	i = -1;
	while (aux[++i] != NULL)
		printf("%s\n", aux[i]);
	free(aux);
	return ;
}
/**
 *
 * Description:		Sets the variable to the designated value.
 *
 * Arguments:		t_instruct *intruction The structure where to find  instruction and arguments..
 *
 * Returns:			Integer with 1 in case there is not an error. 0 in case of error.
 **/
int cmd_export(t_instruct *intruction)
{
	int		i;
	char	**aux;

	if (!check_args(intruction->header->command))
	{
		printf("Minishell: export: `=': not a valid identifier");
		return (0);
	}
	i = -1;
	if (!intruction->arg || !intruction->arg[0])
	{
		print_env_sorted(intruction->header->env);
		return (1);
	}
	while (intruction->arg[++i])
	{
		if (ft_strchr(intruction->arg[i], 0, '=') == NULL )
		{
			if (putenv(intruction->arg[i]) == 0)
				printf("Variable exported succesfully%s\n", intruction->arg[i]);
			else
				printf("error exporting the variale %s\n", intruction->arg[i]);
		}
		else
		{
			aux = ft_split(intruction->arg[i], '=');
			if (setenv(aux[0], aux[1], 1) == 0)
			{
				printf("Variable %s set succesfully with %s\n", aux[0], aux[1]);
			}
			else
			{
				printf("Variable %s failed to set with %s\n", aux[0], aux[1]);
			}
			if (putenv(intruction->arg[i]) == 0)
				printf("Variable exported succesfully%s\n", intruction->arg[i]);
			else
				printf("error exporting the variale %s\n", intruction->arg[i]);
			free_arrchar(aux);
		}
	}
	return (1);
}
