/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:09:19 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/15 12:09:26 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	execute a given command..
*	Argument: 	t_instruct *intruction; structure with the command and arguments.
*	Returns: none
*/
char	*check_file_exists(t_instruct *intruction)
{
	int		i;
	char	**path_arr;
	char	*out;
	struct	stat fileStat;

	out = (char*) malloc(1024 * sizeof(char));
	out[0] = '\0';
	path_arr =  ft_split(getenv("PATH"), ':');
	i = -1;
	while(path_arr && path_arr[++i])
	{
		ft_strlcat(out,path_arr[i],1024);
		ft_strlcat(out,"/",1024);
		ft_strlcat(out,intruction->instruc,1024);
		if(lstat(out,&fileStat) == 0)
			return (out);
		out[0] = '\0';
	}
	free(out);
	return (NULL);
}

/*
*	Descripcion:	adds a string in an array of strings.
*	Argument: 		char **arr --> array where to add 
*					char *str --> adding str
*	Returns: 		resultant array
*/
char	**add_dir_to_arg (char **arr, char *str)
{
	int		i;
	char	**out;

	i = 0;
	while (arr && arr[i])
		i++;
	out = (char **)	malloc( (i + 2) * sizeof(char*));
	out[i + 1] = NULL;
	out[0] = str;
	i = 1;
	while (arr && arr[i])
		out [i] = arr[i - 1];
	free (arr);
	return (out);
}

/*
*	Description:	execute a given command..
*	Argument: 		t_instruct *intruction; structure with the command and arguments.
*	Returns: 		integger : 	0 success 
*								1, error
*/
int cmd_exec(t_instruct *intruction)
{
	char *out;
	out = check_file_exists(intruction);
	if(!out)
		return (0);
	intruction->arg = add_dir_to_arg (intruction->arg, out);
	if(execve(out, intruction->arg, intruction->header->env) == -1)
	{
		printf ("salgo con error\n");
		free(out);
		return (1);
	}
	free(out);
	return (0);
}