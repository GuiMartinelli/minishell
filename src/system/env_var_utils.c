/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:54:38 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/09 17:50:00 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Free and set a pointer to NULL, very useful to save some lines.
 * 
 * @param ptr pointer to be freed
 */
void	free_n_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/**
 * @brief Free a t_var type of struct.
 * 
 * @param var t_var struct to be freed
 */
void	free_var(t_var *var)
{
	free_n_null(var->name);
	free_n_null(var->value);
	var->next = NULL;
	free_n_null(var);
}

char	*ft_getenv(char *name, t_var *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->name, name, ft_strlen(name)) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
