/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:50:02 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/13 11:45:32 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates the shell's built-in env, which writes all environment 
 * variables to a given fd.
 * 
 * @param arg args
 * @param list the environment variables list
 * @param fd the file descriptor to print
 * @return void
 */
void	env(char **arg, t_var *list, int fd)
{
	t_var	*curr;

	if (*arg)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		g_error_status = 1;
		return ;
	}
	curr = list;
	while (curr)
	{
		ft_putstr_fd(curr->name, fd);
		ft_putchar_fd('=', fd);
		if (curr->value)
			ft_putstr_fd(curr->value, fd);
		ft_putchar_fd('\n', fd);
		curr = curr->next;
	}
}
