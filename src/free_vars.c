
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
	printf("paso\n");
	free_arrchar (data->env);
	printf("paso\n");
	free_arrchar(data->cmd_list);
	printf("paso\n");
	free (data->functions_ptr);
	printf("paso\n");
	if(data->command)
		free(data->command);
	printf("paso\n");
	free (data);
}