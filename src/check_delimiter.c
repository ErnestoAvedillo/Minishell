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

char *my_ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

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

char *get_start_delimit(char *str)
{
	int i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (str + i);
}

char *get_end_delimit(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	aux = get_start_delimit(str);
	while (aux[i] && aux[i] != ' ' && aux[i] != '|' && aux[i] != '>')
		i++;
	return ((char*)aux + i);
}

char	*get_delimit(char *str)
{
	char	*aux[2];
	char 	*out;

	aux[0] = get_start_delimit(str);
	aux[1] = get_end_delimit(str);
	out = ft_substr(str, (int)(aux[0] - str), (size_t)(aux[1] - aux[0]));
	return (out);
}

char *insert_in_line(char *cmd, char *str, char *ptr)
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

/*
 *   Checks that the command line does not have following errors
 *   " = " or " =" or "= " --> is not OK
 *   operands should be allways in betewwn blanks
 *
 */
void check_delimiter(t_instruct *instr)
{
	char	*readed;
	char	*delimiter;
	char	*aux;

	delimiter = ft_strdup(instr->in->fd_name);
	instr->in->fd_type = 2;
	aux = ft_itoa(instr->header->contador);
	instr->header->contador++;
	instr->in->fd_name = ft_strjoin("tmp",aux);
	instr->in->fd = open(instr->in->fd_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(aux);
	aux = ft_strjoin(delimiter, ">");
	readed = readline(aux);
	while (ft_strncmp(readed, delimiter, 0, ft_strlen(readed)))
	{
		ft_putstr_fd(readed, instr->in->fd);
		ft_putstr_fd("\n", instr->in->fd );
		free(readed);
		readed = readline(aux);
	}
	free(delimiter);
	free(aux);
	close(instr->in->fd);
	return ;
}
