/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:59:18 by eavedill          #+#    #+#             */
/*   Updated: 2023/06/22 19:59:25 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

//Booleano. Es true si es correcto el control de las comillas
//Estara OK si:
//a) No hay comillas
//b) Si las hay y se han cerrado despues de abrirse.
bool	quotes_ok(char *str)
{
	int		c;
	char	quote;
	bool	quoted_off;

	c = 0;
	quote = '\0';
	quoted_off = true;
	while (str[c])
	{
		if (is_quote(str[c]) && quoted_off)
		{
			quoted_off = false;
			quote = str[c];
		}
		else if (is_quote(str[c]) && !quoted_off && str[c] == quote)
		{
			quoted_off = true;
			quote = '\0';
		}
		c++;
	}
	if (quoted_off == true)
		return (true);
	return (false);
}

int cmd_echo(t_data * data)
{
    char **str;
    char *com;
    int i;

    while(!quotes_ok(data->command))
    {
        com = readline(">");
        //ft_strlcat(data->command, str);
    }
    str =ft_split (data->command, '\"');
    i = -1;
    while (str[++i])
        printf ("%s",str[i]);
    printf ("\n");
    printf ("has entrado en echo con el comando %s.\n", data->command);
    return (1);
}
