/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:48:57 by proberto          #+#    #+#             */
/*   Updated: 2022/01/30 16:35:03 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks for a pipe on the command line.
 * 
 * @param cl char array (acronymous for command line)
 * @return True if there is a pipe, False if there is none or if there is a
 * double pipe (one pipe followed by another pipe)
*/
static int	is_there_a_pipe(char **cl)
{
	while (*cl)
	{
		if (**cl == '|')
		{
			if (*(++cl) && **cl == '|')
				return (FALSE);
			return (TRUE);
		}
		cl++;
	}
	return (FALSE);
}

/**
 * @brief Checks for any redirects on the command line.
 * 
 * @param cl char array (acronymous for command line)
 * @param redirection the possible redirects to inputs (<, <<) and
 * outputs (>, >>)
 * @return True if there is a redirect, False otherwise
*/
static int	is_there_redirections(char **cl, char redirection)
{
	while (*cl && **cl != '|')
	{
		if (**cl == redirection)
			return (TRUE);
		cl++;
	}
	return (FALSE);
}

/**
 * @brief Reset input and output to default.
 * 
 * @param input pointer to the input file descriptor to be reset
 * @param output pointer to the output file descriptor to be reset
 * @return void
*/
void	reset_io(int *input, int *output)
{
	if (*input != STDIN_FILENO)
		close(*input);
	if (*output != STDOUT_FILENO)
		close(*output);
	*output = STDOUT_FILENO;
}

/**
 * @brief Define what will be the input and output of the program.
 * 
 * @param cl char array (acronymous for command line)
 * @param input pointer to the input file descriptor
 * @param output int pointer to the output file descriptor
 * @return void
*/
void	set_io(char **cl, int *fd, int *input)
{
	if (is_there_a_pipe(cl) == TRUE)
		pipe(fd);
	if (is_there_redirections(cl, '>'))
	{
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
		fd[1] = output_redirects(cl);
	}
	if (is_there_redirections(cl, '<'))
	{
		if (*input != STDIN_FILENO)
			close(*input);
		*input = input_redirects(cl);
	}
}
