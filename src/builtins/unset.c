/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:47:03 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/11 16:09:31 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Subroutine to unset variables.
 * 
 * @param var_list variable list
 * @param var_name name of the var to be deleted
 * @return beginning of the node list, may change if the variable to be 
 * deleted is the first
*/
static t_var	*ft_remove(t_var *var_list, char *var_name)
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

/**
 * @brief Simulates unset shell builtin, that delete a variable of a variable
 * list.
 * 
 * @param var_list variable list
 * @param var_name name of the var to be deleted
 * @return beginning of the node list, may change if the variable to be 
 * deleted is the first
 */
t_var	*unset(t_var *var_list, char **var_name)
{
	size_t	i;

	i = 0;
	while (var_name[i])
	{
		var_list = ft_remove(var_list, var_name[i]);
		i++;
	}
	return (var_list);
}
