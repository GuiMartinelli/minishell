/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:54:17 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/14 08:23:21 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	move_index(char **matrix, int index)
{
	while (*matrix[index] != '>')
		index++;
	index++;
	if (matrix[index])
		index++;
	return (index);
}

int	create_file(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd);
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
	while (*matrix)
	{
		if (**matrix == c)
		{
			matrix++;
			return (*matrix);
		}
		matrix++;
	}
	return (NULL);
}

int	output_redirects(char **matrix)
{
	char	*name;
	int		mode;
	int		index;
	int		fd;

	index = 0;
	while (matrix[index] && *matrix[index] != '|')
	{
		mode = check_redirects((matrix + index), '>');
		if (!mode)
			return (1);
		name = file_name((matrix + index), '>');
		if (name == NULL)
			return (-1);
		fd = create_file(name, mode);
		index = move_index(matrix, index);
	}
	return (fd);
}
