/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:47:03 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/07 19:59:45 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*unset(t_var *var_list, char *var_name)
{
	t_var	*curr;
	t_var	*prev;
	size_t	size;

	size = ft_strlen(var_name);
	curr = var_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->name, var_name, size))
		{
			if (prev)
				prev->next = curr->next;
			else
				var_list = var_list->next;
			free_var(curr);
			return (var_list);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (var_list);
}
