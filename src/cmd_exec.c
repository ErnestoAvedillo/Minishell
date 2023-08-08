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
*	Argument: 	t_instruct *instruct; structure with the command and arguments.
*	Returns: none
*/
char	*check_file_exists(t_instruct *instruct)
{
	int			i;
	char		**path_arr;
	char		*out;
	struct stat	file_stat;

	if (lstat(instruct->arg[0], &file_stat) == 0)
		return (ft_strdup(instruct->arg[0]));
	out = (char *)malloc(1024 * sizeof(char));
	out[0] = '\0';
	path_arr = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path_arr && path_arr[++i])
	{
		ft_strlcat(out, path_arr[i], 1024);
		ft_strlcat(out, "/", 1024);
		ft_strlcat(out, instruct->arg[0], 1024);
		if (lstat(out, &file_stat) == 0)
			return (out);
		out[0] = '\0';
	}
	free_arrchar(path_arr);
	free(out);
	return (NULL);
}

/*
*	Descripcion:	adds a string in an array of strings.
*	Argument: 		char **arr --> array where to add 
*					char *str --> adding str
*	Returns: 		resultant array
*/
char	**add_dir_to_arg(char **arr, char *str)
{
	int		i;
	char	**out;

	i = 0;
	while (arr && arr[i])
		i++;
	out = (char **) malloc((i + 2) * sizeof(char *));
	out[i + 1] = NULL;
	out[0] = str;
	i = 0;
	while (arr && arr[i])
	{
		out [i + 1] = arr[i];
		i++;
	}
	free (arr);
	return (out);
}

/*
*	Description:	execute a given command..
*	Argument: 		t_instruct *instruct; structure with the command and arguments.
*	Returns: 		integger : 	0 success 
*								1, error
*/
int	cmd_exec(t_instruct *instruct)
{
	char	*out;
	int		exec;

	out = check_file_exists(instruct);
	if (!out)
		return (0);
	free(instruct->arg[0]);
	instruct->arg[0] = out;
	exec = execve(instruct->arg[0], instruct->arg, instruct->header->env);
	if (exec == -1)
	{
		//printf ("salgo con error\n");
		free(out);
		return (1);
	}
	return (0);
}
