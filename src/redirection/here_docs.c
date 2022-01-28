/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:07:13 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/28 11:48:52 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Receives a string from readline, and the delimiter, if the string
 * is different from delimiter, writes on a temp file, else, close the file
 * 
 * @param str string received from readline function
 * @param eof delimiter
 * @return if the string is dfferent from delimiter, it will return 0, else
 * it returns 1, that means the file is finished
 */
int	write_heredoc(char *str, char *eof)
{
	int	size;
	int	fd;

	if (ft_strlen(str) > ft_strlen(eof))
		size = (int)ft_strlen(str);
	else
		size = (int)ft_strlen(eof);
	fd = open("/tmp/heredoc", O_WRONLY | O_APPEND);
	if (!ft_strncmp(str, eof, size))
	{
		close(fd);
		return (1);
	}
	else
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		close(fd);
		return (0);
	}
}

char	**next_redirect(char **matrix)
{
	while (**matrix != '<')
		matrix++;
	matrix++;
	while (**matrix != '<')
	{
		matrix++;
		if (!*matrix || **matrix == '|')
			return (NULL);
	}
	return (matrix);
}

void	print_err(char *delimiter)
{
	write(1, "minishell: warning: here-document delimited by "
		"end-of-file (wanted `", 69);
	ft_putstr_fd(delimiter, 1);
	write(1, "`)\n", 4);
}

int	heredocs_prompt(char **matrix, char *delimiter)
{
	char	*str;
	int		fd;
	char	**ptr;

	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd);
	while (1)
	{
		str = readline(">");
		if (str == NULL)
		{
			print_err(delimiter);
			break ;
		}
		if (write_heredoc(str, delimiter))
		{
			free(str);
			break ;
		}
		free(str);
	}
	ptr = next_redirect(matrix);
	if (ptr)
		heredocs_prompt(ptr, *(ptr + 1));
	return (1);
}
