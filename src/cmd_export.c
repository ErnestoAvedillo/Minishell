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
bool	check_args(char *str)
{
	int	i;

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
		ft_printf("declare -x %s\n", aux[i]);
	free(aux);
	return ;
}

/**
 *
 * Description:		Sets the variable to the designated value.
 *
 * Arguments:		t_instruct *instr The structure where to find  instruction and arguments..
 *
 * Returns:			Integer with 1 in case there is not an error. 0 in case of error.
 **/
int	cmd_export(t_instruct *instr)
{
	int		i;
	size_t	j;
	char	**aux;
	char	*value;

	if (!check_args(instr->header->command))
	{
		printf("Minishell: export: `=': not a valid identifier");
		return (0);
	}
	i = -1;
	if (!instr->arg || !instr->arg[0])
	{
		print_env_sorted(instr->header->env);
		return (1);
	}
	while (instr->arg[++i])
	{
		if (ft_strchr(instr->arg[i], 0, '=') == NULL )
		{
			j = ft_strlen(instr->arg[i]) + ft_strlen(getenv(instr->arg[i]));
			value = (char *)malloc((j + 2) * sizeof(char));
			value[0] = '\0';
			ft_strlcat(value, instr->arg[i], j + 2);
			ft_strlcat(value, "=", j + 2);
			ft_strlcat(value, getenv(instr->arg[i]), j + 2);
			if (putenv(value) == 0)
				printf("Variable exported succesfully%s\n", value);
			else
				printf("error exporting the variale %s\n", value);
		}
		else
		{
			aux = ft_split(instr->arg[i], '=');
			if (setenv(aux[0], aux[1], 1) == 0)
			{
				printf("Variable %s set succesfully with %s\n", aux[0], aux[1]);
			}
			else
			{
				printf("Variable %s failed to set with %s\n", aux[0], aux[1]);
			}
			if (putenv(instr->arg[i]) == 0)
				printf("Variable exported succesfully %s\n", instr->arg[i]);
			else
				printf("error exporting the variale %s\n", instr->arg[i]);
			free_arrchar(aux);
			value = ft_strdup(instr->arg[i]);
		}
		instr->header->env = actualize_env(instr->header->env, value, 1);
		if (!instr->header->env)
			return (-1);
	}
	return (1);
}
