/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:50:02 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/12 18:07:01 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates the shell's built-in env, which writes all environment 
 * variables to a given fd.
 * 
 * @param list the environment variables list
 * @param fd the file descriptor to print
 * @return void
 */
void	env(t_var *list, int fd)
{
	t_var	*curr;

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
