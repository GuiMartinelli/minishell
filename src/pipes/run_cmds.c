/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:27 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/18 21:05:20 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(char **matrix)
{
	while (*matrix)
	{
		if (**matrix == '|')
			return (1);
		matrix++;
	}
	return(0);
}

void	run_cmds(char **matrix, char **envp, int input, int output)
{
	t_cmd	*cmd;
	int		fd[2];
	int		pid;

	(void)input;
	cmd = malloc(sizeof(t_cmd));
	while (matrix)
	{
		matrix = parse_cmd(cmd, matrix, envp);
		if (*matrix && **matrix == '|')
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(input, 0);
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				execve(cmd->name, cmd->option, cmd->env);
			}
			else
			{
				wait(NULL);
				close(fd[1]);
				matrix++;
				run_cmds(matrix, envp, fd[0], output);
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(input, 0);
				dup2(output, 1);
				execve(cmd->name, cmd->option, cmd->env);
				close(input);
			}
			else
			{
				wait(NULL);
				close(input);
				break ;
			}
		}
	}
//	static int	fd[2];
//	char	**path;
//	t_cmd	*cmd;
//
//	(void)input;
//	cmd = malloc(sizeof(t_cmd));
//	path = parse_paths(envp);
//	if (is_pipe(matrix))
//	{
//		if (fd[0] == 0)
//			pipe(fd);
//		if (launch_builtins(matrix[0], matrix, env_list, fd[1]) == TRUE)
//			close(fd[1]);
//		else
//		{
//			matrix = parse_cmd(cmd, matrix, envp);
//			launch_execve(cmd->name, cmd->option, cmd->env, fd);
//		}
//		while (**matrix != '|')
//			matrix++;
//		matrix++;
//		run_cmds(matrix, envp, fd[0], output, env_list);
//	}
//	else
//	{
//		if (launch_builtins(matrix[0], matrix, env_list, output) == TRUE)
//			;
//		else
//		{
//			fd[0] = input;
//			fd[1] = output;
//			launch_execve(check_path(path, matrix[0]), matrix, envp, fd);
//		}
//	}
//	free_matrix(path);
}