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

void	fill_heredoc(t_instruct *instr, char *delimit)
{
	char	*texto;
	char	*out;

	texto = ft_strjoin(delimit, ">");
	out = cmd_read(texto);
	while (out && end_of_heredoc(out, delimit) && g_out_status == -3)
	{
		if (instr->in->expand)
			out = expand_variables(out);
		ft_putstr_fd(out, instr->in->fd);
		ft_putstr_fd("\n", instr->in->fd);
		free(out);
		out = cmd_read(texto);
	}
	free(texto);
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
	char	*aux[2];
	int		pid;
	int		status;

	g_out_status = -3;
	instr->in->fd_type = 2;
	aux[1] = ft_strdup(instr->in->fd_name);
	aux[0] = ft_itoa(instr->header->contador);
	instr->header->contador++;
	instr->in->fd_name = ft_strjoin("/tmp/tmp", aux[0]);
	instr->in->fd = open(instr->in->fd_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	reset_signals();
	pid = fork();
	if (pid == -1)
	{
		print_err("minishell: error while forking");
		g_out_status = 1;
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, han_c_fork);
		fill_heredoc(instr, aux[1]);
	}
	wait(&status);
	g_out_status = WEXITSTATUS(status);
	if (g_out_status == 130 || g_out_status == 131)
		instr->header->execute = false;
	close(instr->in->fd);
	free(aux[0]);
	free(aux[1]);
	return ;
}
