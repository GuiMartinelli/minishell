/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:21:15 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/16 10:06:01 by proberto         ###   ########.fr       */
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
int	export(t_var **env, t_var *var)
{
	if (new_variable(env, var->name, var->value))
		return (1);
	return (0);
}
