
#include "../inc/minishell.h"

void	free_arrchar(char **arrchr)
{
	int	i;

	if(arrchr)
	{
		i = -1;
		while (arrchr[++i])
		{
			free (arrchr[i]);
			arrchr[i] = NULL;
		}
		free(arrchr);
		arrchr = NULL;
	}
}

void    free_vars(t_data *data)
{
	free_arrchar(data->cmd_list);
	free_arrchar(data->oper_list);
	free (data->functions_ptr);
	if(data->command)
	{
		free(data->command);
		data->command = NULL;
	}
	free (data);
	data = NULL;
}