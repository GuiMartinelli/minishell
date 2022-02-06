/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:54:17 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 08:22:54 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_file(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd);
}

int	output_redirects(char **matrix)
{
	char	*name;
	int		mode;
	int		fd;

	fd = STDOUT_FILENO;
	while (check_redirects(matrix, '>'))
	{
		mode = check_redirects(matrix, '>');
		if (!mode)
			return (1);
		name = file_name(matrix, '>');
		if (!name || *name == '|' || *name == '<' || *name == '>')
			return (file_error(name));
		if (mode > 0 && fd != STDOUT_FILENO)
			close(fd);
		fd = create_file(name, mode);
		matrix++;
	}
	return (fd);
}
