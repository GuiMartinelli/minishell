/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:07:13 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 16:53:32 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if there is other heredocs in the command line.
 * 
 * @param cl char array (acronym for command line)
 * @return the pointer to the next heredoc or NULL if there is none
 */
static char	**next_redirect(char **cl)
{
	while (**cl != '<')
		cl++;
	cl++;
	while (**cl != '<')
	{
		cl++;
		if (!*cl || **cl == '|')
			return (NULL);
	}
	return (cl);
}

/**
 * @brief Print error message.
 * 
 * @param delimiter the keyword for the EOF (end of file)
 * @return void
 */
static void	print_err(char *delimiter)
{
	write(2, "minishell: warning: here-document delimited by "
		"end-of-file (wanted `", 69);
	ft_putstr_fd(delimiter, 2);
	write(2, "`)\n", 4);
}

/**
 * @brief Receives a string from readline, and the delimiter, if the string
 * is different from delimiter, writes on a temp file, else, close the file
 * 
 * @param input string received from readline function
 * @param eof the keyword for the EOF (end of file)
 * @return if the string is different from delimiter, it will return 0, else
 * it returns 1, that means the file is finished
 */
static int	write_heredoc(char *input, char *eof)
{
	int	size;
	int	fd;

	if (ft_strlen(input) > ft_strlen(eof))
		size = (int)ft_strlen(input);
	else
		size = (int)ft_strlen(eof);
	fd = open("/tmp/heredoc", O_WRONLY | O_APPEND);
	if (!ft_strncmp(input, eof, size))
	{
		close(fd);
		return (1);
	}
	else
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		close(fd);
		return (0);
	}
}

/**
 * @brief Read and submit to write_heredoc function the string received from 
 * readline.
 * 
 * @param delimiter the keyword for the EOF (end of file)
 * @return void
 */
static void	read_and_write(char *delimiter)
{
	char	*input;

	signal(SIGINT, interrupt_here_docs);
	while (TRUE)
	{
		input = readline("> ");
		if (input == NULL)
		{
			print_err(delimiter);
			exit(0);
		}
		if (write_heredoc(input, delimiter))
		{
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

/**
 * @brief Open a temp file and write the string received from readline.
 * 
 * @details readline is executed in a subprocess so that the SIGINT is captured
 * and handled outside the scope of the main process, this causes the command 
 * prompt to be returned when the signal is received
 * @param cl char array (acronym for command line)
 * @param delimiter the keyword for the EOF (end of file)
 * @return fd of the temp file
 */
int	heredocs_prompt(char **cl, char *delimiter)
{
	char	**ptr;
	int		fd;
	int		pid;
	int		status;

	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd);
	signal(SIGINT, SIG_IGN);
	status = 0;
	pid = fork();
	if (pid == 0)
		read_and_write(delimiter);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			g_error_status = 130;
	}
	ptr = next_redirect(cl);
	if (ptr && g_error_status != 130)
		heredocs_prompt(ptr, *(ptr + 1));
	return (open("/tmp/heredoc", O_RDONLY));
}
