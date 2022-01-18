/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:27 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/17 22:05:35 by guferrei         ###   ########.fr       */
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

void	run_cmds(char **matrix, char **envp, int input, int output, t_var *env_list)
{
	int		fd[2];
	//int	index;
	char	**path;

	(void)input;
	path = parse_paths(envp);
	if (is_pipe(matrix))
	{
		pipe(fd);
		//0
		//1
		//2
		
		//3
		//4
		if (launch_builtins(matrix[0], matrix, env_list, fd[1]) == TRUE)
			;
		else
			launch_execve(check_path(path, matrix[0]), matrix, envp, fd);
		while (**matrix != '|')
			matrix++;
		matrix++;
		run_cmds(matrix, envp, fd[0], output, env_list);
	}
	else
	{
		if (launch_builtins(matrix[0], matrix, env_list, output) == TRUE)
			;
		else
		{
			launch_execve(check_path(path, matrix[0]), matrix, envp, fd);
		}
	}
	free_matrix(path);
}