/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:47:03 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/08 19:26:35 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates unset shell builtin, that delete a variable of a variable
 * list.
 * 
 * @param var_list variable list
 * @param var_name name of the var to be deleted
 * @return beggining of the var list, may change if the variable to be deleted
 * is the first one
 */
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
