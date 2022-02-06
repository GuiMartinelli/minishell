/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:22:14 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 12:39:02 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_default_io(t_cmd *cmd)
{
	cmd->read = STDIN_FILENO;
	cmd->write = STDOUT_FILENO;
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
void	set_io(char **cl, t_cmd *cmd)
{
	int			fd[2];
	static int	input;

	set_default_io(cmd);
	if (is_there_a_pipe(cl) == TRUE)
	{
		pipe(fd);
		cmd->read = input;
		cmd->write = fd[1];
		input = fd[0];
	}
	else
	{
		cmd->read = input;
		input = STDIN_FILENO;
	}
	if (is_there_redirections(cl, '>'))
	{
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
		cmd->write = output_redirects(cl);
	}
	if (is_there_redirections(cl, '<'))
	{
		if (cmd->read != STDIN_FILENO)
			close(cmd->read);
		cmd->read = input_redirects(cl);
	}
}
