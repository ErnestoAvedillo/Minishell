/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:54:53 by eavedill          #+#    #+#             */
/*   Updated: 2023/08/07 19:54:56 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_out_status;

char	*my_ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!little || !little[0])
		return ((char *)(big));
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		if (big[i] == little[j])
		{
			k = i;
			while (big[k] == little[j] && big[k] && little[j] && k < len)
			{
				k++;
				j++;
			}
			if (!little[j] && k <= len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

char	*get_delimit(char *str)
{
	char	*aux[2];
	char	*out;

	aux[0] = get_start_delimit(str);
	aux[1] = get_end_delimit(str);
	out = ft_substr(str, (int)(aux[0] - str), (size_t)(aux[1] - aux[0]));
	return (out);
}

char	*insert_in_line(char *cmd, char *str, char *ptr)
{
	char	*out;
	char	*aux;

	out = ft_substr(cmd, 0, (size_t)(ptr - cmd));
	out = concat_cmd(out, str);
	aux = ft_strdup(get_end_delimit(ptr));
	out = concat_cmd(out, aux);
	free(cmd);
	return (out);
}

static bool	end_of_heredoc(char *str1, char *str2)
{
	int		i;

	i = ft_max(ft_strlen(str1), ft_strlen(str2));
	if (!ft_strncmp(str1, str2, 0, i))
		return (false);
	return (true);
}

/*
 *   Checks that the command line does not have following errors
 *   " = " or " =" or "= " --> is not OK
 *   operands should be allways in betewwn blanks
 *
 * In function aux[0] corresonds to the auxiliar variable
 * In function aux[1] corresonds to the readed variable
 * In function aux[2] corresonds to the delimiter variable
 */
void	check_delimiter(t_instruct *instr)
{
	char	*aux[3];

	g_out_status = -3;
	aux[2] = instr->in->fd_name;
	instr->in->fd_type = 2;
	aux[0] = ft_itoa(instr->header->contador);
	instr->header->contador++;
	instr->in->fd_name = ft_strjoin("/tmp/tmp", aux[0]);
	instr->in->fd = open(instr->in->fd_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(aux[0]);
	aux[0] = ft_strjoin(aux[2], ">");
	aux[1] = cmd_read(aux[0]);
	while (aux[1] && end_of_heredoc(aux[1], aux[2]))
	{
		ft_putstr_fd(aux[1], instr->in->fd);
		ft_putstr_fd("\n", instr->in->fd);
		free(aux[1]);
		aux[1] = cmd_read(aux[0]);
	}
	free(aux[2]);
	free(aux[1]);
	free(aux[0]);
	close(instr->in->fd);
	return ;
}
