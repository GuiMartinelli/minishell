/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:22:14 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 17:35:21 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Set the default input and output file descriptor.
 * 
 * @param cmd command structure
 * @return void
 */
void	set_default_io(t_cmd *cmd)
{
	cmd->read = STDIN_FILENO;
	cmd->write = STDOUT_FILENO;
}

/**
 * @brief Reset input and output file descriptors to default and close them 
 * if they are open.
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
 * @brief Set io subfunction.
 * 
 * @param cmd command structure
 * @param input read file descriptor
 * @return void
 */
void	set_io_sub(t_cmd *cmd, int *input)
{
	cmd->read = *input;
	*input = STDIN_FILENO;
}

/**
 * @brief Define what will be the input and output of the program.
 * 
 * @param cl char array (acronym for command line)
 * @param cmd command structure
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
		set_io_sub(cmd, &input);
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
