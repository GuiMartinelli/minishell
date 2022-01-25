/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:27 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/25 18:35:59 by proberto         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	free(cmd->option);
	free(cmd->name);
	free(cmd);
}

void	ft_print_matrix(char **matrix)
{
	while(*matrix)
		printf("\nmatrix: %s\n\n", *matrix++);
}

void	run_cmds(char **matrix, char **envp, int input, int output, t_var *env_list)
{
	t_cmd	*cmd;
	int		fd[2];
	int		pid;

	(void)input;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	cmd = malloc(sizeof(t_cmd));
	// ft_print_matrix(matrix);
	matrix = parse_cmd(cmd, matrix, envp);
	if (*matrix && **matrix == '|')
	{
		pipe(fd);
		if (launch_builtins(cmd->option[0], cmd->option, env_list, fd[1]))
		{
			close(fd[1]);
			matrix++;
			run_cmds(matrix, envp, fd[0], output, env_list);
		}
		else
		{
			pid = fork();
			signal(SIGINT, interrupt_process);
			signal(SIGQUIT, quit_process);
			if (pid == 0)
			{
				dup2(input, 0);
				dup2(fd[1], 1);
				if (input != 0)
					close(input);
				close(fd[1]);
				execve(cmd->name, cmd->option, cmd->env);
			}
			else
			{
				wait(NULL);
				close(fd[1]);
				matrix++;
				run_cmds(matrix, envp, fd[0], output, env_list);
				close(fd[0]);
			}
		}
	}
	else
	{
		if (*matrix && (**matrix == '<' || **matrix == '>'))
		{	
			output = output_redirects(matrix);
			if (output <= 1)
			{
				if (input != 0)
					close(input);
				input = input_redirects(matrix);
			}
			while (*matrix && **matrix != '|')
				matrix++;
			// printf("\nmatrix: %s\n", *matrix);
			// printf("cmd: %s\narg: %s\n", cmd->option[0], cmd->option[1]);
			// printf("Output: %d\n", output);
		}	
		if (launch_builtins(cmd->option[0], cmd->option, env_list, output))
		{
			if (input != 0)
				close(input);
			if (output != 1)
				close(output);
		}
		else
		{
			pid = fork();
			signal(SIGINT, interrupt_process);
			signal(SIGQUIT, quit_process);
			if (pid == 0)
			{
				dup2(input, 0);
				dup2(output, 1);
				execve(cmd->name, cmd->option, cmd->env);
				if (input != 0)
					close(input);
				if (output != 1)
					close(output);
			}
			else
			{
				wait(NULL);
				if (input != 0)
					close(input);
				if (output != 1)
					close(output);
			}
		}
	}
	if (*matrix && **matrix == '|')
		run_cmds(++matrix, envp, STDIN_FILENO, STDOUT_FILENO, env_list);
	free_cmd(cmd);
}
