/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:59:47 by proberto          #+#    #+#             */
/*   Updated: 2022/02/01 08:34:13 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	number_of_args(char **matrix)
{
	int	size;

	size = 0;
	while (*matrix)
	{
		matrix++;
		size++;
	}
	return (size);
}

int	valid_exit(char *status)
{
	if (!status)
		return (1);
	while (*status)
	{
		if (!ft_isdigit(*status))
			return (0);
		status++;
	}
	return (1);
}

/**
 * @brief Simulates the shell's built-in exit, which exits the shell.
 * 
 * @return void 
 */
void	ft_exit(char **exit_status, t_var *env_list)
{
	int	ex;
	int	args;

	args = number_of_args(exit_status);
	if (args > 2)
		write(2, "bash: exit: too many arguments\n", 32);
	else if (!valid_exit(exit_status[1]))
	{
		write(2, "bash: exit: ", 13);
		ft_putstr_fd(*exit_status, 2);
		write(2, ": numeric argument required\n", 29);
	}
	else
	{
		if (args == 1)
			ex = 0;
		else
			ex = ft_atoi(exit_status[1]);
		free_matrix(exit_status);
		free_var_list(env_list);
		exit(ex);
	}
}
