/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:21:16 by proberto          #+#    #+#             */
/*   Updated: 2022/02/12 23:48:10 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if there is a redirection in the command line.
 * 
 * @param cl char array (acronym for command line)
 * @param c redirect character (</>)
 * @return int
 */
int	check_redirects(char **cl, char c)
{
	while (*cl)
	{
		if (**cl == c)
		{
			if (*(*cl + 1) == c)
				return (2);
			else
				return (1);
		}
		cl++;
	}
	return (0);
}

/**
 * @brief Return the file name.
 * 
 * @param cl char array (acronym for command line)
 * @param c redirect character (</>)
 * @return char* 
 */
char	*file_name(char **cl, char c)
{
	char	*file;

	file = NULL;
	while (*cl && **cl != '|')
	{
		if (**cl == c && c == '<' && *(cl + 1))
			return (*(cl + 1));
		else if (**cl == c && c == '>' && *(cl + 1))
			return (*(cl + 1));
		cl++;
	}
	return (file);
}

/**
 * @brief Print a error message.
 * 
 * @param name file name
 * @return int
 */
int	file_error(char *name)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (name)
	{
		ft_putstr_fd(name, STDERR_FILENO);
		write(2, "'\n", 2);
	}
	else
		ft_putendl_fd(" newline'", STDERR_FILENO);
	return (-1);
}
