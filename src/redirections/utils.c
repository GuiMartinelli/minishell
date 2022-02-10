/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:21:16 by proberto          #+#    #+#             */
/*   Updated: 2022/02/10 09:21:06 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Return index for next redirect.
 * 
 * @param cl char array (acronym for command line)
 * @param index 
 * @param c redirect character (</>)
 * @return int 
 */
int	move_index(char **cl, int index, char c)
{
	while (*cl[index] != c)
		index++;
	index++;
	if (cl[index])
		index++;
	return (index);
}

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
	write(2, "bash: syntax error near unexpected token `", 43);
	if (name)
	{
		write(2, &*name, 1);
		write(2, "'\n", 2);
	}
	else
		write(2, "newline'\n", 10);
	return (-1);
}
