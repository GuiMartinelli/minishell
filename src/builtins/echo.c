/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:42:18 by proberto          #+#    #+#             */
/*   Updated: 2021/12/20 19:08:07 by proberto         ###   ########.fr       */
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
void	echo(char **str, int fd)
{
	char	flag;
	size_t	i;

	i = 1;
	if (str[i] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	if (ft_strncmp(str[i], "-n", ft_strlen(str[i])) == 0)
	{
		flag = TRUE;
		i++;	
	}
	else
		flag = FALSE;
	while (str[i])
	{
		if ((flag == TRUE && i > 2) || (flag == FALSE && i > 1))
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(str[i++], fd);
	}
	if (flag == FALSE)
		ft_putchar_fd('\n', fd);
}
