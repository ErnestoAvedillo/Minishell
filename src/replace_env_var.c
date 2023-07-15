/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:46:18 by eavedill          #+#    #+#             */
/*   Updated: 2023/07/11 22:46:23 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_env_var(char *str)
{
	int 	i;
	int 	j;
	char 	*variable;
	char 	*value;
	char 	*out;

//	printf(" entrada str %s\n", str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
			if(!str[i])
				return (str);
		}
		if (str[i] == '$')
		{
			j = i;
			while (str[j] && (str[j] != ' ' && str[j] != '\"'))
				j++;
			variable = ft_substr(str, i + 1, j - i - 1);
			value = getenv(variable);
			j = (int)(ft_strlen(str) - ft_strlen(variable) + ft_strlen(value));
			out = (char *)malloc(j *sizeof(char));
			out[j - 1] = '\0';
//			printf("La longitud de la cadena es j= %i, -- %i\n",j, (int)ft_strlen(out));
			j = - 1;
			while (out[++j])
			{
				if (j < i)
				{
					out[j] = str[j];
//			printf("1 salida i= %i j = %i len value= %i len variable %i resutl = %i out %s str %s\n", i, j, (int)ft_strlen(value) ,(int)ft_strlen(variable), j + (int)ft_strlen(variable) - (int)ft_strlen(value) ,out, str);
				}
				else if (j > i + (int)ft_strlen(value) - 1)
				{
					out[j] = str[j + (int)ft_strlen(variable) - (int)ft_strlen(value) + 1];
//			printf("2 salida i= %i j = %i len value= %i len variable %i resutl = %i --> %c out %s str %s\n", i, j, (int)ft_strlen(value) ,(int)ft_strlen(variable), j + (int)ft_strlen(variable) - (int)ft_strlen(value), str[j + (int)ft_strlen(variable) - (int)ft_strlen(value) + 1] ,out, str);
				}
				else if (value)
				{
//					if (value[j-i] == '\0')
//						printf ("pongo cero\n");
					out[j] = value[j - i];
//			printf("3 salida i= %i j = %i len value= %i len variable %i resutl = %i out %s str %s\n", i, j, (int)ft_strlen(value) ,(int)ft_strlen(variable), j + (int)ft_strlen(variable) - (int)ft_strlen(value) ,out, str);
				}
			}
//			printf("he salido\n");
			free(variable);
			free(str);
			str = out;
			out = NULL;
			i += ft_strlen(value) - 1;
		}
	}
//	printf(" salida str %s\n", str);
	return (str);
}