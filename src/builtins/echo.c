/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:42:18 by proberto          #+#    #+#             */
/*   Updated: 2022/02/10 08:40:11 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates the shell's built-in echo, which prints the string passed 
 * as argument.
 * 
 * @details if there is a flag (-n) in the str, don't print a newline
 * @param str the string to print
 * @param fd the file descriptor to print
 * @return void
 */
void	echo(char **str, int fd)
{
	char	flag;
	size_t	i;

	i = 1;
	flag = FALSE;
	if (str[i] != NULL)
	{
		if (ft_strncmp(str[i], "-n\0", 3) == 0)
		{
			flag = TRUE;
			i++;
		}
		while (str[i])
		{
			if (command_args_delimiter(str[i]))
				break ;
			if (((flag == TRUE && i > 2) || (flag == FALSE && i > 1))
				&& *str[i - 1])
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(str[i++], fd);
		}
	}
	if (flag == FALSE)
		ft_putchar_fd('\n', fd);
}
