/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/01 23:21:52 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	file_not_found(char *name)
{
	write(2, "bash: ", 7);
	ft_putstr_fd(name, 2);
	write(2, ": No such file or directory\n", 29);
	return (-1);
}

int	input_redirects(char **matrix)
{
	char	*name;
	int		mode;
	int		fd;
	int		i;

	i = 0;
	while (matrix[i] && *matrix[i] != '|')
	{
		mode = check_redirects((matrix + i), '<');
		if (!mode)
			return (0);
		name = file_name((matrix + i), '<');
		if (!name || *name == '|' || *name == '<' || *name == '>')
			return (file_error(name));
		if (mode == 2)
		{
			heredocs_prompt(matrix, name);
			return (open("/tmp/heredoc", O_RDONLY));
		}
		else
		{
			if (fd != STDIN_FILENO && *matrix[i] == '<')
			{
				close(fd);
				fd = open(name, O_RDONLY);
				if (fd == -1)
					return (file_not_found(name));
			}
			i = move_index(matrix, i, '<');
		}
	}
	return (fd);
}
