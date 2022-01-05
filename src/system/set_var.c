/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:30:25 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/05 18:41:03 by guferrei         ###   ########.fr       */
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

	splitted = ft_split(str, '=');
	if (name_validation(splitted[0]))
		new_variable(local, splitted[0], splitted[1]);
	free(splitted[0]);
	free(splitted[1]);
	free(splitted);
}
