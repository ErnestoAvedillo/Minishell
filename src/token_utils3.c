/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_quotes(char *str, int pos, bool *quot)
{
	if (pos == -1)
	{
		quot[0] = 0;
		quot[1] = 0;
		quot[2] = 0;
		return ;
	}
	if (!quot[1] && str[pos] == '\'')
		quot[0] = !quot[0];
	else if (!quot[0] && str[pos] == '\"')
		quot[1] = !quot[1];
	if (str[pos] == '\\' && (str[pos + 1] == '\\' || str[pos + 1] == '$'))
		quot[2] = !quot[2];
	else if (str[pos] != '$' && str[pos - 1] != '\\')
		quot[2] = false;
}

/* Parte de fill_instruct */
char	*process_quotes(char *str)
{
	bool	quot[3];
	int		i;

	check_quotes(str, -1, quot);
	i = 0;
	while (i <= (int)ft_strlen(str))
	{
		check_quotes(str, i, quot);
		if (str[i] == '\\' && !quot[1] && !quot[0])
			ft_strrmchr(str, i);
		else if ((!quot[1] && str[i] == '\'') || (!quot[0] && str[i] == '\"'))
		{
			ft_strrmchr(str, i);
			i--;
		}
		i++;
	}
	return (str);
}

void	prepare_for_split(char *str)
{
	bool	quot[3];
	int		i;

	check_quotes(str, -1, quot);
	i = 0;
	while (str[i])
	{
		check_quotes(str, i, quot);
		if (str[i] == '\t')
			str[i] = ' ';
		if ((quot[0] && str[i] == ' ') || (quot[1] && str[i] == ' '))
			str[i] = (char)0xff;
		i++;
	}
}

/* Parte de fill_instruct */
void	split_args(t_instruct *inst, char *str)
{
	int	j;
	int	i;

	j = -1;
	inst->arg = ft_split(str, ' ');
	while (inst->arg[++j])
	{
		i = -1;
		while (inst->arg[j][++i])
			if (inst->arg[j][i] == (char)0xff)
				inst->arg[j][i] = ' ';
	}
	i = -1;
	while (inst->arg[++i])
		inst->arg[i] = process_quotes(inst->arg[i]);
}

/* Parte de fill_instruct */
char	*expand_variables(char *str, t_instruct *inst)
{
	int		i;
	bool	quot[3];

	check_quotes(str, -1, quot);
	i = 0;
	while (str[i])
	{
		check_quotes (str, i, quot);
		if ((str[i] == '$' && str[i + 1] == '\'' && !quot[0])
			|| (str[i] == '$' && str[i + 1] == '\"' && !quot[1]))
		{
			ft_strrmchr(str, i);
			i--;
		}
		else if (str[i] == '$' && ((str[i + 1] == '\"' && quot[1])
				|| str[i + 1] == '\0' || str[i + 1] == ' '
				|| (str[i + 1] == '\'' && quot[0]) || (str[i + 1] == '/')))
			;
		else if (str[i] == '$' && !quot[0] && !quot[2])
		{
			str = replace_env_var(str, i, inst->header->out_status);
			i--;
		}
		i++;
	}
	return (str);
}

char	*expand_home_dir(char *str)
{
	int		i;
	bool	quot[3];

	check_quotes(str, -1, quot);
	i = 0;
	while (str[i])
	{
		check_quotes (str, i, quot);
		if (str[i] == '~' && !quot[0] && !quot[1])
			str = repl_home_dir(str, i);
		if (str[i] == '-' && !quot[0] && !quot[1])
			str = repl_old_dir(str, i);
		i++;
	}
	return (str);
}

/*
*   Descriptinon:	Fill all data for the current instrucion.
*   Arguments:		t_instruct *inst : the variable to fill in.
*					char *str The variable where it is the instruction.
*					int start position where is t\starting the instruction
*					int end where the instruction ends.
*   Returns:		Nothing
*/
char	*fill_instruct2(t_instruct *inst, char *str)
{
	str = expand_home_dir(str);
	str = expand_variables(str, inst);
	prepare_for_split(str);
	str = check_ext_files(inst, str);
	split_args(inst, str);
	return (str);
}
