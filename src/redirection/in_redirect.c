/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/31 09:16:30 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	file_error(char *name)
{
	write(1, "bash: syntax error near unexpected token `", 43);
	if (name)
	{
		write(1, &*name, 1);
		write(1, "'\n", 2);
	}
	else
		write(2, "newline'\n", 10);
}

void	file_not_found(char *name)
{
	write(2, "bash: ", 7);
	ft_putstr_fd(name, 2);
	write(2, ": No such file or directory\n", 29);
}

int	input_redirects(char **matrix)
{
	char	*name;
	int		mode;
	int		fd;

	mode = check_redirects(matrix, '<');
	if (!mode)
		return (0);
	name = file_name(matrix, '<');
	if (!name || *name == '|' || *name == '<' || *name == '>')
	{
		file_error(name);
		return (-1);
	}
	if (mode == 2)
	{
		heredocs_prompt(matrix, name);
		return (open("/tmp/heredoc", O_RDONLY));
	}
	else
	{
		fd = open(name, O_RDONLY);
		if (fd == -1)
			file_not_found(name);
		return (fd);
	}
}
