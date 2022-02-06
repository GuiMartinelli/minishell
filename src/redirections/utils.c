/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:21:16 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 08:23:19 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	move_index(char **matrix, int index, char c)
{
	while (*matrix[index] != c)
		index++;
	index++;
	if (matrix[index])
		index++;
	return (index);
}

int	check_redirects(char **matrix, char c)
{
	while (*matrix)
	{
		if (**matrix == c)
		{
			if (*(*matrix + 1) == c)
				return (2);
			else
				return (1);
		}
		matrix++;
	}
	return (0);
}

char	*file_name(char **matrix, char c)
{
	char	*file;

	file = NULL;
	while (*matrix && **matrix != '|')
	{
		if (**matrix == c && c == '<' && *(matrix + 1))
			return (*(matrix + 1));
		else if (**matrix == c && c == '>' && *(matrix + 1))
			return (*(matrix + 1));
		matrix++;
	}
	return (file);
}

int	file_error(char *name)
{
	write(1, "bash: syntax error near unexpected token `", 43);
	if (name)
	{
		write(1, &*name, 1);
		write(1, "'\n", 2);
	}
	else
		write(2, "newline'\n", 10);
	return (-1);
}
