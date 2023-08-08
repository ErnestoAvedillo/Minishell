/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*   Descriptinon:	returns the pre_operation of the instruction. 
*					NOTE: pos in the string should be at least 1 or 2 to have some operands. 
*   Arguments:		char *str The variable where it is the instruction.
*					int pos position where is starting the instruction
*					int end where yhe instruction ends.
*   Returns:		The pointer of the string
*/
char	*get_pre_oper(char *str, int pos)
{
	char	*pre_oper;

	pre_oper = NULL;
	if (pos > 1)
	{
		if (str[pos - 1] == '<' && str[pos - 2] == '<')
			pre_oper = ft_strdup ("<<");
		if (str[pos - 1] == '>' && str[pos - 2] == '>')
			pre_oper = ft_strdup (">>");
		if (pre_oper != NULL)
			return (pre_oper);
	}
	if (pos > 0)
	{
		if (str[pos - 1] == '<')
			pre_oper = ft_strdup ("<");
		else if (str[pos - 1] == '>')
			pre_oper = ft_strdup (">");
		else if (str[pos - 1] == '|')
			pre_oper = ft_strdup ("|");
	}
	return (pre_oper);
}

/*
*   Descriptinon:	returns the pre_operation of the instruction.
*   Arguments:		char *str The variable where it is the instruction.
*					int pos position where is ending the instruction
*					int end where yhe instruction ends.
*   Returns:		The pointer of the string
*/
char	*get_post_oper(char *str, int pos)
{
	char	*post_oper;

	post_oper = NULL;
	if (pos < (int)ft_strlen(str) - 2)
	{
		if (str[pos] == '<' && str[pos + 1] == '<')
			post_oper = ft_strdup ("<<");
		if (str[pos] == '>' && str[pos + 1] == '>')
			post_oper = ft_strdup (">>");
		if (post_oper != NULL)
			return (post_oper);
	}
	if (pos < (int)ft_strlen(str) - 1)
	{
		if (str[pos] == '<')
			post_oper = ft_strdup ("<");
		else if (str[pos] == '>')
			post_oper = ft_strdup (">");
		else if (str[pos] == '|')
			post_oper = ft_strdup ("|");
	}
	return (post_oper);
}

/*
 *   Descriptinon:	Replace all charachtes of the string equal of c1 
 *					and replaces them from c2.
 *   Arguments:		char *str The variable to be splited.
 *   Returns:		Double pointer where to find the array.
 */
void	replace_char_in_str(char *str, unsigned int c1, unsigned int c2)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == (char)c1)
			str[i] = c2;
}


/*
*   Descriptinon:	Fill all data for the current instrucion.
*   Arguments:		t_instruct *inst : the variable to fill in.
*					char *str The variable where it is the instruction.
*					int start position where is t\starting the instruction
*					int end where the instruction ends.
*   Returns:		Nothing
*/
char	*fill_instruct(t_instruct *inst, char *str)
{
	int		i;
	int		j;
	bool	quot[2];
	char	*ptr;

	quot[0] = false;
	quot[1] = false;
	ptr = ft_strnstr(str, "echo",ft_strlen(str));
	i = -1;
	if (ptr != NULL && ptr < str+ ft_strlen(str))
	{
		while(i <= (int)ft_strlen(str))
		{
			if (str[i] == '\\' && !quot[1] && !quot[0])
				ft_strrmchr(str, i);
			else if (!quot[1] && str[i] == '\'')
			{
				quot[0] = !quot[0];
				ft_strrmchr(str, i);
				i--;
			}
			else if (!quot[0] && str[i] == '\"')
			{
				quot[1] = !quot[1];
				ft_strrmchr(str, i);
				i--;
			}
			else if (str[i] == '$' && !quot[1] && !quot[0] && (str[i + 1] == ' ' || str[i + 1] == '\"'))
			{
				ft_strrmchr(str, i);
				i--;
			}
			else if (str[i] == '$' && ((!quot[0] && !quot[1]) || quot[1]))
				str = replace_env_var(str, i, inst->header->out_status);
			else if (str[i] == '~' && !quot[0] && !quot[1])
				str = repl_home_dir(str, i);
			else if ((quot[0] && str[i] == ' ') || (quot[1] && str[i] == ' '))
				str[i] = (char)0xff;
			i++;
		}

		inst->arg = ft_split(str, ' ');
		j = -1;
		while (inst->arg[++j])
		{
			i = -1;
			while (inst->arg[j][++i])
				if (inst->arg[j][i] == (char)0xff)
					inst->arg[j][i] = ' ';
		}
		inst->instruc = ft_strdup(inst->arg[0]);
	}
	else
	{
		inst->arg = ft_split(str, ' ');
		inst->instruc = ft_strdup(inst->arg[0]);
	}
	return (str);
}
