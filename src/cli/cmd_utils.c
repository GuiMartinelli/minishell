/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:50:08 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/03 21:57:04 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_errors(t_cmd *cmd, int error_status)
{
	free_cmd(cmd);
	g_error_status = error_status;
	return (-1);
}

int	check_error(int input, int fd, t_cmd *cmd)
{
	if (input == -1 || fd == -1)
		return (handle_errors(cmd, 1));
	if (!cmd->option || !cmd->option[0])
		return (handle_errors(cmd, 0));
	return (0);
}

void	set_default_io(int fd[2])
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
}

void	free_cmd(t_cmd *cmd)
{
	free_n_null(cmd->option);
	free_n_null(cmd->name);
	free_n_null(cmd);
}

void	define_signal(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
