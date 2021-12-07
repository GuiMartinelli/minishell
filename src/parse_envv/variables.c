/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:12:52 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/07 20:40:00 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	overwrite_var(t_var *var, char *value)
{
	free((void *)var->value);
	var->value = ft_strdup(value);
	if (!var->value)
		return (1);
	return (0);
}

int	update_var(t_var *var_list, char *name, char *value)
{
	t_var	*curr;

	if (!var_list)
		return (0);
	curr = var_list;
	while (curr->next != NULL)
	{
		if (!ft_strncmp(curr->name, name, 30))
		{
			if (overwrite_var(curr, value))
				return (-1);
			else
				return (1);
		}
		else
			curr = curr->next;
	}
	return (0);
}

t_var	*create_var(char *name, char *value)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

int	new_variable(t_var **lst, char *name, char *value)
{
	t_var	*new_var;
	t_var	*curr;

	if (update_var(*lst, name, value))
		return (0);
	new_var = create_var(name, value);
	if (!new_var)
		return (1);
	if (*lst == NULL)
	{
		*lst = new_var;
		return (0);
	}
	curr = *lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_var;
	return (0);
}

t_var	*env_variables(char **env)
{
	char	**split;
	t_var	*var_list;

	var_list = NULL;
	while (*env)
	{
		split = ft_split_value(*env, '=');
		new_variable(&var_list, split[0], split[1]);
			free(split[0]);
		free(split[1]);
		free(split);
		*env++;
	}
	return (var_list);
}
