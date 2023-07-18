/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:02:21 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*   Descriptinon:	I search the position in str where it finishes any of the 
*					chars present in *c
*   Arguments:		char *str : trinw where to look for in.
					int ini Starting position to log for
					char (array of chars to look for
*   Returns:		The position where the character has been found or 
*					the end of tring pos charachter.
*/
/*static size_t	ft_nextstartpos(char const *str, size_t ini, char *c)
{
	size_t	i;
	size_t	j;

	i = ini;
	j = 0;
	while (str[i] != c[j] && c[j])
		j++;
	if (j == ft_strlen(c))
		return (i);
	while (str[i] == c[j] && str[i])
		i++;
	return (i);
}
*/
/*
*   Descriptinon:	Search the position in str where any of the charachters in *c are 
*					found.
*   Arguments:		char *str : trinw where to look for in.
					int ini Starting position to log for
					char (array of chars to look for
*   Returns:		The position where the character has been found or the "\0" pos.
*					charachter.
*/
static size_t	ft_nextendpos(char const *str, size_t ini, char *c)
{
	size_t	i;
	size_t	j;

	i = ini;
	j = 0;
	while (str[i] && str[i] != c[j])
	{
		while (c[j])
		{
			if( str[i] == c[j] )
				return (i);
			j++;
		}
		i++;
		j = 0;
	}
	return (i);
}

/*
 *   Descriptinon:	Separate the commands by its operators.
 *   Arguments:		t_data *data : The structure data where the command and the env pointer is.
 *   Returns:		The tokenized instruction separated by the operators.
 */
t_instruct *tokenize(t_data *data)
{
    t_instruct	*first_inst;
    t_instruct	*instruct[2];
	int			start_pos;
	int			end_pos;


	first_inst = init_instructions(data);
	instruct[0] = first_inst;
	if (first_inst == NULL)
		return (NULL);
	start_pos = 0;
	while (start_pos <= (int)ft_strlen(data->command))
	{
		end_pos = ft_nextendpos(data->command, start_pos, "|><");
		printf("variable Words %i - %i\n", start_pos, end_pos);
		fill_instruct(instruct[0], data->command, start_pos, end_pos);
		start_pos = end_pos + 1;
		printf("variable Words %i - %i\n", start_pos, end_pos);
		if (start_pos <= (int)ft_strlen(data->command))
		{
			instruct[1] = init_instructions(data);
			instruct[0]->next = instruct[1];
			instruct[1]->prev = instruct[0];
			instruct[0] = instruct[1];
		}
	}
	print_inst(first_inst);
    return (first_inst);
}

