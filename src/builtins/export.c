/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:21:15 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/22 17:52:50 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates export shell builtin, that adds a new variable at
 * environment variables list.
 * 
 * @param env environment variables list
 * @param var variable to be appended at environment variables list
 * @return returns 0 if success or 1 if something fails
 */
int	export(char **arg, t_var *env_list)
{
	char	**name;
	char	*value;
	size_t	i;
	size_t	j;

	i = 1;
	while (arg[i] != NULL)
	{
		value = ft_strchr(arg[i], '=');
		name = ft_split(arg[i], '=');
		if (*name == NULL)
			break ;
		new_variable(&env_list, name[0], ++value);
		j = 0;
		while (name[j] != NULL)
			free(name[j++]);
		free(name);
		i++;
	}
	return (0);
}
