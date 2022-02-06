/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:54:17 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 17:02:47 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Output redirects subfunction.
 * 
 * @disclaimer: mode 1 is equivalent to > (truncate)
 * mode 2 is equivalent to >> (append)
 * @param file file name
 * @param mode open mode
 * @return int 
 */
static int	create_file(char *file, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd);
}

/**
 * @brief Create (if it doesn't exist) or open a file and return its 
 * file descriptor.
 * 
 * @param cl char array (acronym for command line)
 * @return fd 
 */
int	output_redirects(char **cl)
{
	char	*name;
	int		mode;
	int		fd;

	fd = STDOUT_FILENO;
	while (check_redirects(cl, '>'))
	{
		mode = check_redirects(cl, '>');
		if (!mode)
			return (1);
		name = file_name(cl, '>');
		if (!name || *name == '|' || *name == '<' || *name == '>')
			return (file_error(name));
		if (mode > 0 && fd != STDOUT_FILENO)
			close(fd);
		fd = create_file(name, mode);
		cl++;
	}
	return (fd);
}
