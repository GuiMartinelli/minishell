/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:42:18 by proberto          #+#    #+#             */
/*   Updated: 2021/11/30 16:38:31 by proberto         ###   ########.fr       */
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
void	echo(char *str)
{
	char	*strtrim;

	if (*str == 39)
	{
		strtrim = ft_strtrim(str, "'");
		printf("%s\n", strtrim);
		free(strtrim);
	}
	else if (*str == 34)
	{
		strtrim = ft_strtrim(str, "\"");
		printf("%s\n", strtrim);
		free(strtrim);
	}
	else
		printf("%s\n", str);
}
