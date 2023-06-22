
#include "../inc/minishell.h"

void	free_arrchar(char **arrchr)
{
	int	i;

	if(arrchr)
	{
		i = -1;
		while (arrchr[++i])
			free (arrchr[i]);
		free(arrchr);
	}
}

void    free_vars(t_data *data)
{
	free_arrchar (data->env);
	free_arrchar(data->cmd_list);
	free (data->functions_ptr);
	if(data->command)
		free(data->command);
	free (data);
}