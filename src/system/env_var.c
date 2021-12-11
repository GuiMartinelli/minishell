/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:12:52 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/10 21:23:31 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Overwrite a existing variable with a new value.
 * 
 * @param var variable to be updated
 * @param value new value to var
 * @return returns 0 if success or 1 if malloc fails
 */
int	overwrite_var(t_var *var, char *value)
{
	free((void *)var->value);
	var->value = ft_strdup(value);
	if (!var->value)
		return (1);
	return (0);
}

/**
 * @brief Check if a variable already exists in a list.
 * 
 * @param var_list variables list to be checked
 * @param name name of the new variable to check
 * @param value value of the new variable
 * @return returns 0 if the variable don't exists yet, 1 if exists
 * and was updated or -1 if something failed
 */
int	update_var(t_var *var_list, char *name, char *value)
{
	t_var	*curr;

	if (!var_list)
		return (0);
	curr = var_list;
	while (curr->next != NULL)
	{
		if (!ft_strncmp(curr->name, name, ft_strlen(curr->name)))
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

/**
 * @brief Create a var struct, allocating memory and setting its value 
 * and name.
 * 
 * @param name name of the new variable
 * @param value value of the new variable
 * @return t_var struct created
 */
t_var	*create_var(char *name, char *value)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

/**
 * @brief Create a new t_var struct or update a existing one and append 
 * it at the end of a variables linked list.
 * 
 * @param lst linked list where new variable will be appended
 * @param name name of the new variable
 * @param value value of the new variable
 * @return return 1 if something fails allocating memory, or 0 if success
 */
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

/**
 * @brief Parses the environment variables matrix and return it as a t_var
 * structs linked list.
 * 
 * @param env environment variables matrix, that main function receive as param
 * @return t_var* 
 */
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
