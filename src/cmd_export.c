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
 * Description:		exports the variable when is given with the value. 
 * 					In this case when no value is given in the variable.
 *
 * Arguments:		t_instruct *instr The structure where to find  
 * 					instruction and arguments..
 * 					char *var, the string where to find the variable to be exported
 *
 * Returns:			NONE
 **/
static char	**exp_no_val(char *var, char **env)
{
	size_t	j;
	char	*value;
	char	**aux;

	aux = env;
	j = ft_strlen(var) + ft_strlen(getenv(var));
	value = (char *)malloc((j + 2) * sizeof(char));
	value[0] = '\0';
	ft_strlcat(value, var, j + 2);
	ft_strlcat(value, "=", j + 2);
	ft_strlcat(value, getenv(var), j + 2);
	if (putenv(value) == 0)
		aux = actualize_env(env, value, 1);
	free(value);
	return (aux);
}

/**
 * Description:		exports the variable when is given with the value.
 * 					In this case when the value is given in the variable.
 *
 * Arguments:		t_instruct *instr The structure where to find
 * 					instruction and arguments..
 * 					char *var, the string where to find the variable to be exported
 *
 * Returns:			NONE
 **/
static char	**exp_val(char *var, char **env)
{
//	char	**aux;
	char	**out;
	char	*value;

	out = env;
	value = ft_strdup(var);
//	if (setenv(aux[0], aux[1], 1) == 0)
//	aux = ft_split(value, '=');
	if (putenv(value) == 0)
	{
		out = actualize_env(env, var, 1);
	}
//	free_arrchar(aux);
	return (out);
}

/**
 *
 * Description:		Sets the variable to the designated value.
 *
 * Arguments:		t_instruct *instr The structure where to find  
 * 					instruction and arguments..
 *
 * Returns:			Integer with 1 in case there is not an error. 0 in case of error.
 **/
int	cmd_export(t_instruct *instr)
{
	int		i;

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
			instr->header->env = exp_no_val(instr->arg[i], instr->header->env);
		else
			instr->header->env = exp_val(instr->arg[i], instr->header->env);
		if (!instr->header->env)
			return (-1);
	}
	return (1);
}
