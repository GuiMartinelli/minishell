/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:47:03 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/13 12:04:06 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Subroutine to unset variables.
 * 
 * @param env_list environment variables list
 * @param var_name name of the var to be deleted
 * @return beginning of the node list, may change if the variable to be 
 * deleted is the first
*/
static t_var	*ft_remove(t_var *env_list, char *var_name)
{
	t_var	*curr;
	t_var	*prev;
	size_t	size;

	size = ft_strlen(var_name);
	curr = env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->name, var_name, size))
		{
			if (prev)
				prev->next = curr->next;
			else
				env_list = env_list->next;
			free_var(curr);
			return (env_list);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (env_list);
}

/**
 * @brief Simulates the shell's built-in unset, which excludes a variable from 
 * a variable list.
 * 
 * @param env_list environment variables list
 * @param var_name name of the var to be deleted
 * @return beginning of the node list, may change if the variable to be 
 * deleted is the first
 */
t_var	*unset(t_var *env_list, char **var_name)
{
	size_t	i;
	char	*val;

	i = 0;
	val = "1";
	while (var_name[i])
	{
		if (valid_var(var_name[i], val, "minishell: unset: `") == TRUE)
			env_list = ft_remove(env_list, var_name[i]);
		else
			g_error_status = 1;
		i++;
	}
	return (env_list);
}
