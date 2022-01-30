/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:48:57 by proberto          #+#    #+#             */
/*   Updated: 2022/01/30 15:48:15 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	reset_io(int *input, int *output)
{
	if (*input != STDIN_FILENO)
		close(*input);
	if (*output != STDOUT_FILENO)
		close(*output);
	*output = STDOUT_FILENO;
}

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
