/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/02/04 12:10:49 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launch_builtins(t_cmd *cmd, char **matrix, t_var *env_list, int fd)
{
	g_error_status = 0;
	if (ft_strncmp(cmd->option[0], "pwd",
			comp_size(cmd->option[0], "pwd")) == 0)
		pwd(fd);
	else if (ft_strncmp(cmd->option[0], "env",
			comp_size(cmd->option[0], "env")) == 0)
		env(env_list, fd);
	else if (ft_strncmp(cmd->option[0], "echo",
			comp_size(cmd->option[0], "echo")) == 0)
		echo(cmd->option, fd);
	else if (ft_strncmp(cmd->option[0],
			"cd", comp_size(cmd->option[0], "cd")) == 0)
		cd(cmd->option[1], env_list);
	else if (ft_strncmp(cmd->option[0], "export",
			comp_size(cmd->option[0], "export")) == 0)
		export(env_list, &cmd->option[1]);
	else if (ft_strncmp(cmd->option[0], "unset",
			comp_size(cmd->option[0], "unset")) == 0)
		env_list = unset(env_list, &cmd->option[1]);
	else if (ft_strncmp(cmd->option[0], "exit",
			comp_size(cmd->option[0], "exit")) == 0)
		ft_exit(cmd->option, env_list, matrix, cmd);
	else
		return (FALSE);
	return (TRUE);
}

int	launch_execve(t_cmd *cmd, int input, int output)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	define_signal();
	if (pid == 0)
	{
		dup2(input, 0);
		dup2(output, 1);
		if (execve(cmd->name, cmd->option, cmd->env) == -1)
		{
			perror("minishell");
			return (-1);
		}
		if (input != STDIN_FILENO)
			close(input);
		if (output != STDOUT_FILENO)
			close(output);
	}
	else if (pid == -1)
		ft_putendl_fd("\nFailed forking child..", 2);
	wait(&status);
	reset_io(&input, &output);
	return (status);
}

void	launch(t_cmd *cmd, int fd[2], int *input)
{
	if (cmd->name && access(cmd->name, F_OK) == 0)
	{
		if (launch_execve(cmd, *input, fd[1]))
		{
			if (g_error_status != 131 && g_error_status != 130)
				g_error_status = 1;
		}
		else
		{
			if (g_error_status != 130)
				g_error_status = 0;
		}
	}
	else
	{
		g_error_status = 127;
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->option[0], 2);
		write(2, "\n", 1);
	}
}

static int	run_command_line(char **cl, t_env_var *env, int input, int output)
{
	t_cmd		*cmd;
	int			fd[2];
	const char	**aux;

	aux = (const char **)cl;
	(void)input;
	(void)output;
	set_default_io(fd);
	cmd = ft_calloc(1, sizeof(t_cmd));
	cl = parse_cmd(cmd, cl, env->envp, env->list);
	if (!cl)
		return (handle_errors(cmd, 2));
	set_io(cl, fd, &input);
	if (check_error(input, fd[1], cmd))
		return (-1);
	if (launch_builtins(cmd, (char **)aux, env->list, fd[1]))
		reset_io(&input, &fd[1]);
	else
		launch(cmd, fd, &input);
	free_cmd(cmd);
	while (*cl && **cl++ != '|')
		;
	if (*cl && **cl != '|')
		run_command_line(cl, env, fd[0], fd[1]);
	return (0);
}

void	eval(char *command_line, t_var *env_list, char **envp)
{
	char		**run;
	t_env_var	env;

	env.envp = envp;
	env.list = env_list;
	run = string_parse(command_line, env_list, envp);
	if (!*run)
	{
		free_matrix(run);
		return ;
	}
	run_command_line(run, &env, STDIN_FILENO, STDOUT_FILENO);
	free_matrix(run);
}
