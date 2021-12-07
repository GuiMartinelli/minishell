/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:50:02 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/07 19:47:42 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_var *list, int fd)
{
	t_var	*curr;

	curr = list;
	while (curr)
	{
		ft_putstr_fd(curr->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(curr->value, fd);
		ft_putchar_fd('\n', fd);
		curr = curr->next;
	}
}
