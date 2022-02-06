/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 17:07:46 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle input redirects errors and set global variable status.
 * 
 * @param name file name
 * @return int 
 */
static int	file_not_found(char *name)
{
	write(2, "bash: ", 7);
	ft_putstr_fd(name, 2);
	write(2, ": No such file or directory\n", 29);
	g_error_status = 1;
	return (-1);
}

/**
 * @brief Input redirects subfunction.
 * 
 * @param file file name
 * @param c char array (acronym for command line)
 * @param fd file descriptor
 * @return fd 
 */
static int	open_file(char *file, char c, int fd)
{
	if (c == '<')
	{
		if (fd != STDIN_FILENO)
			close(fd);
		fd = open(file, O_RDONLY);
	}
	return (fd);
}

/**
 * @brief Open a file and return its file descriptor.
 * 
 * @param cl char array (acronym for command line)
 * @return fd
 */
int	input_redirects(char **cl)
{
	char	*name;
	int		mode;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	while (cl[i] && *cl[i] == '<')
	{
		mode = check_redirects((cl + i), '<');
		if (!mode)
			return (0);
		name = file_name((cl + i), '<');
		if (!name || *name == '|' || *name == '<' || *name == '>')
			return (file_error(name));
		if (mode == 2)
			return (heredocs_prompt(cl, name));
		fd = open_file(name, *cl[i], fd);
		if (fd == -1)
			return (file_not_found(name));
		i = move_index(cl, i, '<');
	}
	return (fd);
}
