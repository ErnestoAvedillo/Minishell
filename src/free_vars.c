
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

void	free_inst(t_instruct *first_instruction)
{
	t_instruct *instructions;

	instructions =  first_instruction;
	while(instructions)
	{
		free(instructions->instruc);
		instructions->instruc = NULL;
		free_arrchar(instructions->arg);
		first_instruction = instructions->next;
		free(instructions);
		instructions = first_instruction;
	}
}