/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:42:18 by proberto          #+#    #+#             */
/*   Updated: 2021/12/07 20:47:29 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Prints the string passed as argument.
 * 
 * @todo get the value of the variable when there is a $
 * @param str The string to print
 * @return void
 */
void	echo(char *op, char *str)
{
	char	*strtrim;
	char	breakline;

	if (ft_strncmp(op, "-n", ft_strlen(op)) == 0)
		breakline = 0;
	else
		breakline = '\n';
	if (*str == 39)
	{
		strtrim = ft_strtrim(str, "'");
		printf("%s%c", strtrim, breakline);
		free(strtrim);
	}
	else if (*str == 34)
	{
		strtrim = ft_strtrim(str, "\"");
		printf("%s%c", strtrim, breakline);
		free(strtrim);
	}
	else
		printf("%s\n", str);
}
