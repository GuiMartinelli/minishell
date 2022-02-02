/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:54:17 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/02 18:16:58 by proberto         ###   ########.fr       */
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
	char	*file;

	file = NULL;
	while (*matrix && **matrix != '|')
	{
		if (**matrix == c && c == '<')
			return (*(matrix + 1));
		else if (**matrix == c && c == '>')
			return (*(matrix + 1));
		matrix++;
	}
	return (file);
}

int	output_redirects(char **matrix)
{
	char	*name;
	int		mode;
	// int		index;
	int		fd;

	// index = 0;
	fd = STDOUT_FILENO;
	// printf("\n#####matrix: %s\n", *matrix);
	// while (*matrix && **matrix != '>')
	// 	matrix++; 
	while (check_redirects(matrix, '>'))
	{
		mode = check_redirects(matrix, '>');
		// printf("\n*******mode: %d\n", mode);
		if (!mode)
			return (1);
		name = file_name(matrix, '>');
		if (!name || *name == '|' || *name == '<' || *name == '>')
			return (file_error(name));
		if (mode > 0 && fd != STDOUT_FILENO)
			close(fd);
		fd = create_file(name, mode);
		// printf("\n*******matrix: %s\n", *matrix);
		// printf("\n*******fd: %d\n", fd);
		matrix++;
	}
	return (fd);
}
