/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:50:02 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/08 19:26:17 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates env shell builtin, and writes every environment variables
 * in a given fd.
 * 
 * @param list list of variables to be writed
 * @param fd file descriptor to write
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
