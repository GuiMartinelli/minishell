/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:31:27 by proberto          #+#    #+#             */
/*   Updated: 2022/02/12 23:45:29 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Search and launch the correct built-in function. 
 * 
 * @param cmd command structure
 * @param cl char array (acronym for command line)
 * @param env_list environment variables list
 * @return true if any built-ins were executed, false otherwise
 */
static int	launch_builtins(t_cmd *cmd, char **cl, t_var **env_list)
{
	g_error_status = 0;
	if (ft_strncmp(cmd->arg[0], "pwd",
			comp_size(cmd->arg[0], "pwd")) == 0)
		pwd(cmd->write);
	else if (ft_strncmp(cmd->arg[0], "env",
			comp_size(cmd->arg[0], "env")) == 0)
		env(*env_list, cmd->write);
	else if (ft_strncmp(cmd->arg[0], "echo",
			comp_size(cmd->arg[0], "echo")) == 0)
		echo(cmd->arg, cmd->write);
	else if (ft_strncmp(cmd->arg[0],
			"cd", comp_size(cmd->arg[0], "cd")) == 0)
		cd(&cmd->arg[1], *env_list);
	else if (ft_strncmp(cmd->arg[0], "export",
			comp_size(cmd->arg[0], "export")) == 0)
		export(*env_list, &cmd->arg[1]);
	else if (ft_strncmp(cmd->arg[0], "unset",
			comp_size(cmd->arg[0], "unset")) == 0)
		*env_list = unset(*env_list, &cmd->arg[1]);
	else if (ft_strncmp(cmd->arg[0], "exit",
			comp_size(cmd->arg[0], "exit")) == 0)
		ft_exit(cmd->arg, *env_list, cl, cmd);
	else
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Launch execve subfunction.
 * 
 * @param cmd command structure
 * @param input read file descriptor
 * @param output write file descriptor
 * @param envp environment variables passed to the program
 * @return int
 */
static int	launch_execve_sub(t_cmd *cmd, int input, int output, char **envp)
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
		if (execve(cmd->path, cmd->arg, envp) == -1)
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
		ft_putendl_fd("\nFailed forking child..", STDERR_FILENO);
	wait(&status);
	reset_io(&input, &output);
	return (status);
}

/**
 * @brief Search and launch the right executable 
 * (based on the PATH variable or by using relative or absolute path).
 * 
 * @param cmd command structure
 * @param envp environment variables passed to the program through the main 
 * function
 * @return void
 */
static void	launch_execve(t_cmd *cmd, char **envp)
{
	int	exit;

	if (cmd->path && access(cmd->path, F_OK) == 0)
	{
		exit = launch_execve_sub(cmd, cmd->read, cmd->write, envp);
		if (exit)
		{
			if (g_error_status != 131 && g_error_status != 130)
				if (WIFEXITED(exit))
				g_error_status = WEXITSTATUS(exit);
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
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg[0], 2);
		write(2, "\n", 1);
		reset_io(&cmd->read, &cmd->write);
	}
}

/**
 * @brief Handle error and set global variable status.
 * 
 * @param cmd command structure
 * @param error_status number of error
 * @return int
 */
static int	handle_errors(t_cmd *cmd, int error_status)
{
	free_cmd(cmd);
	g_error_status = error_status;
	return (-1);
}

/**
 * @brief Parse and execute the command line.
 * 
 * @param cmd command structure
 * @param cl char array (acronym for command line)
 * @param env structure containing the environment variables (list and envp)
 * @return int
 */
int	run_cl(t_cmd *cmd, char **cl, t_env_var *env)
{
	const char	**aux;

	aux = (const char **)cl;
	cl = parse_cmd(cmd, cl, env->list);
	if (!cl)
		return (handle_errors(cmd, 2));
	set_default_io(&cmd->read, &cmd->write);
	set_io(cl, cmd);
	if (cmd->read == -1 || cmd->write == -1)
		return (handle_errors(cmd, 2));
	if (cmd->arg && *cmd->arg && launch_builtins(cmd, (char **)aux, &env->list))
		reset_io(&cmd->read, &cmd->write);
	else if (cmd->arg && cmd->arg[0])
		launch_execve(cmd, env->envp);
	else
		if (cmd->write != STDOUT_FILENO)
			close(cmd->write);
	free_cmd(cmd);
	while (*cl && **cl++ != '|')
		;
	if (*cl && **cl != '|')
		run_cl(cmd, cl, env);
	reset_io(&cmd->read, &cmd->write);
	return (0);
}
