/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2021/12/07 19:31:01 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	format(char *command_line, t_cmd *cmd)
{
	char	*strtrim;

	(void)cmd;
	strtrim = ft_strtrim(command_line, "' '\t");
	printf("%s\n", strtrim);
	free(strtrim);
}

int	launch_builtins(char *cmd, char *op, char *arg, t_cmd *env_list)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "pwd", len) == 0)
		pwd();
	else if (ft_strncmp(cmd, "env", len) == 0)
	 	env(env_list, 1);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		echo(op, arg);
	else if (ft_strncmp(cmd, "cd", len) == 0)
		cd(arg);
	// else if (ft_strncmp(cmd, "export", len) == 0)
	// 	export();
	// else if (ft_strncmp(cmd, "unset", len) == 0)
	// 	unset();
	// else if (ft_strncmp(cmd, "exit", len) == 0)
	// 	b_exit();
	else
		return (FALSE);
	return (TRUE);
}

void	eval(char *command_line)
{
	t_cmd	cmd;

	format(command_line, &cmd);
	// launch_builtins(cmd.name, cmd.option, cmd.arg);
}
