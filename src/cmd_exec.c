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

static char	**get_arr_path(void)
{
	char		**path_arr;

	if (!getenv("PATH"))
		path_arr = ft_split(CUR_PATH, ':');
	else
		path_arr = ft_split(getenv("PATH"), ':');
	return (path_arr);
}

static char	*check_file_paths(char *file )
{
	char		*out;
	struct stat	file_stat;
	int			i;
	char		**path_arr;

	path_arr = get_arr_path();
	out = (char *)malloc(1024 * sizeof(char));
	out[0] = '\0';
	i = -1;
	while (path_arr && path_arr[++i])
	{
		ft_strlcat(out, path_arr[i], 1024);
		ft_strlcat(out, "/", 1024);
		ft_strlcat(out, file, 1024);
		if (lstat(out, &file_stat) == 0)
		{
			free_arrchar(path_arr);
			return (out);
		}
		out[0] = '\0';
	}
	free_arrchar(path_arr);
	free (out);
	return (NULL);
}

/*
*	execute a given command..
*	Argument: 	t_instruct *instruct; structure with the command and arguments.
*	Returns: none
*/
char	*check_file_exists(t_instruct *instruct)
{
	char		*out;
	struct stat	file_stat;

	if ((instruct->arg[0][0] == '.' && instruct->arg[0][1] == '/') || \
			instruct->arg[0][0] == '/' )
	{
		if (lstat(instruct->arg[0], &file_stat) == 0)
			return (ft_strdup(instruct->arg[0]));
		else
			return (NULL);
	}
	out = check_file_paths(instruct->arg[0]);
	if (out != NULL)
		return (out);
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

	if (ft_strlen(instruct->arg[0]) == 0)
		return (0);
	out = check_file_exists(instruct);
	if (!out)
	{
		print_err("minishell: %s : command not found\n", instruct->arg[0]);
		return (127);
	}
	free(instruct->arg[0]);
	instruct->arg[0] = out;
	exec = execve(instruct->arg[0], instruct->arg, instruct->header->env);
	if (exec == -1)
	{
		print_err("minishell: %s : command not foun\n", instruct->arg[0]);
		free(out);
		return (exec);
	}
	return (0);
}
