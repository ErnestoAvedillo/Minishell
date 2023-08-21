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
*					NOTE: pos in the string should be at least 1 or 2 to 
*					have some operands. 
*   Arguments:		char *str The variable where it is the instruction.
*					int pos position where is starting the instruction
*					int end where yhe instruction ends.
*   Returns:		The pointer of the string
*/
/*char	*get_pre_oper(char *str, int pos)
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
*/
/*
*   Descriptinon:	returns the pre_operation of the instruction.
*   Arguments:		char *str The variable where it is the instruction.
*					int pos position where is ending the instruction
*					int end where yhe instruction ends.
*   Returns:		The pointer of the string
*/
/*char	*get_post_oper(char *str, int pos)
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


*/
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
