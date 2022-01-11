/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/01/11 07:48:59 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

char	**format(char *command_line)
{
	return (ft_split(command_line, ' '));
}

int	launch_builtins(char *cmd, char **arg, t_var *env_list)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "pwd", len) == 0)
		pwd(1);
	else if (ft_strncmp(cmd, "env", len) == 0)
	 	env(env_list, 1);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		echo(arg, 1);
	else if (ft_strncmp(cmd, "cd", len) == 0)
		cd(arg[1], env_list);
	else if (ft_strncmp(cmd, "export", len) == 0)
		export(&arg[1], env_list);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		env_list = unset(env_list, &arg[1]);
	// else if (ft_strncmp(cmd, "exit", len) == 0)
	// 	b_exit();
	else
		return (FALSE);
	return (TRUE);
}

void	launch_execve(char *path, char **arg, char **envp)
{
	pid_t	pid;

	if (access(path, F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, arg, envp) == -1)
			{
				perror("minishell");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid == -1)
			ft_putendl_fd("\nFailed forking child..", 2);
		else
			wait(NULL);
	}
	else
		ft_putendl_fd("minishell: command not found: ", 2);
}

void	eval(char *command_line, t_var *env_list, char **envp)
{
	char 	**run;
	char 	**path;
	char 	*valid_path;
	int		i;

	run = format(string_parse(command_line, env_list, NULL));
	path = parse_paths(envp);
	if (*run == NULL || *path == NULL)
		return ;
	valid_path = check_path(path, run[0]);
	if (valid_path == NULL)
		valid_path = ft_strdup(run[0]);
	if (launch_builtins(run[0], run, env_list) == TRUE)
		i = 0;
	else
		launch_execve(valid_path, run, envp);
	i = 0;
	while (run[i])
		free(run[i++]);
	i = 0;
	while (path[i])
		free(path[i++]);
	free(run);
	free(path);
	free(valid_path);
}
