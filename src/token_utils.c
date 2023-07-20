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
					NOTE: pos in the string should be at least 1 or 2 to have some operands. 
*   Arguments:		char *str The variable where it is the instruction.
*					int pos position where is starting the instruction
*					int end where yhe instruction ends.
*   Returns:		The pointer of the string
*/
char	*get_pre_oper(char *str, int pos)
{
	char *pre_oper;

	pre_oper = NULL;
	if (pos > 1)
	{
		//if (!ft_strncmp(str,"<<",pos - 2, 2))
		if (str[pos - 1] == '<' && str[pos - 2] == '<')
			pre_oper = ft_strdup ("<<");
		//else if (!ft_strncmp(str,">>",pos - 2, 2))
		if (str[pos - 1] == '>' && str[pos - 2] == '>')
			pre_oper = ft_strdup (">>");
		if(pre_oper != NULL)
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
	char *post_oper;

	post_oper = NULL;
	if (pos < (int)ft_strlen(str) - 2)
	{
		//if (!ft_strncmp(str,"<<",pos + 2, 2))
		if (str[pos] == '<' && str[pos + 1] == '<')
			post_oper = ft_strdup ("<<");
		//else if (!ft_strncmp(str,">>",pos + 2, 2))
		if (str[pos] == '>' && str[pos + 1] == '>')
			post_oper = ft_strdup (">>");

		if(post_oper != NULL)
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
 *   Descriptinon:	Replace all charachtes beteween quotes.
 *   Arguments:		char *str The variable to be splited.
 *   Returns:		nothing.
 */
void	replace_char_btw_quotes(char *str, unsigned int c1, unsigned int c2)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (j == 0 && str[i] == '\'')
		{
			str[i] = ' ';
			j = 1;
		}
		if (j == 0 && str[i] == '\"')
		{
			str[i] = ' ';
			j = 2;
		}
		while (j != 0)
		{
			i++;
			if (str[i] && str[i] == (char) c1)
				str[i] = (char)c2;
			if (j == 1 && str[i] == '\'')
			{
				str[i] = ' ';
				j = 0;
			}
			else if (j == 2 && str[i] == '\"')
			{
				str[i] = ' ';
				j = 0;
			}
		}
	}
}

/*
 *   Descriptinon:	Replace all charachtes of the string equal of c1 
 *					and replaces them from c2.
 *   Arguments:		char *str The variable to be splited.
 *   Returns:		Double pointer where to find the array.
 */
void	replace_char(char *str, unsigned int c1, unsigned int c2)
{
	int i;

	i = -1;
	while(str[++i])
		if(str[i] == (char)c1)
			str[i] = c2;
}

/*
	*   Descriptinon:	Returns an array of all arguments separeted by those that
	*					have the charachters " or '.
	*   Arguments:		char *str The variable to be splited.
	*   Returns:		Double pointer where to find the array.
	*/
char **get_special_args(char *str)
{
	char **args;
	int i;

	replace_char_btw_quotes(str, ' ', 254);
	args = ft_split(str, ' ');
	i = -1;
	while (args && args[++i])
		replace_char(args[i], 254, ' ');
	return (args);
}

/*
*   Descriptinon:	Fill all data for the current instrucion.
*   Arguments:		t_instruct *inst : the variable to fill in.
*					char *str The variable where it is the instruction.
*					int start position where is t\starting the instruction
*					int end where the instruction ends.
*   Returns:		Nothing
*/
void	fill_instruct(t_instruct *inst, char *str, int start, int end)
{
	char *words;
	char *ptr;

	//printf("la variable str es %s -- %i -- %i\n",str, start, end);
	inst->pre_oper = get_pre_oper(str,start);
	inst->post_oper = get_post_oper(str,end);
//	printf("la pre oper es %s -- %c%c el postoper es %s -- %c%c \n",inst->pre_oper,str[start - 1],str[start - 2],inst->post_oper,str[end],str[end + 1]);
	while (str[start] && str[start] == ' ')
		start ++;
	ptr = ft_strchr(str, start, ' ');
	if (ptr == NULL || end < (int)(ptr - str))
		inst->instruc = ft_substr(str, start, end - start);
	else
		inst->instruc = ft_substr(str, start, (int)(ptr - str) - start);
	start = (int)(ptr - str);
	words = ft_substr(str, start, end - start);
//	printf("la instruccion es %s los argumentos %s -- %i -- %i -- ptr %i\n",inst->instruc,words, start, end ,(int)(ptr - str));
	if (words[0])
	{
		words = replace_env_var(words);
		if (ft_strchr(words, 0, '\'') == NULL && ft_strchr(words, 0, '\"') == NULL)
			inst->arg = ft_split(words, ' ');
		else
			inst->arg = get_special_args(words);
	}
	free(words);
}
