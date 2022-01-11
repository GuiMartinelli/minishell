/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:30:25 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/11 11:19:48 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	name_validation(char *name)
{
	int	index;

	index = 0;
	if (name[index] != '_' && !ft_isalpha(name[index]))
		return (0);
	index++;
	while (name[index])
	{
		if (name[index] != '_' && !ft_isalnum(name[index]))
			return (0);
		else
			index++;
	}
	return (1);
}

void	set_var(char *str, t_var **local)
{
	char	**splitted;
	char	**var;
	int		index;

	index = 0;
	splitted = ft_split(str, ' ');
	while (splitted[index])
	{
		var = ft_split(splitted[index], '=');
		if (name_validation(var[0]))
			new_variable(local, var[0], var[1]);
		free(var[0]);
		free(var[1]);
		free(var);
		free(splitted[index]);
		index++;
	}
	free(splitted[index]);
	free(splitted);
}
