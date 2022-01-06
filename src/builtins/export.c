/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:21:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/07 21:06:22 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees array of variables.
 * 
 * @param key array of variables
 * @return void
 */
static void	ft_free(char **key)
{
	size_t	i;

	i = 0;
	while (key[i] != NULL)
		free(key[i++]);
	free(key);
}

/**
 * @brief Checks if the variable name is valid.
 * 
 * @param name variable name
 * @return TRUE if the variable name is invalid, FALSE otherwise
 */
static int	invalid_name(char *name)
{
	size_t	i;
	int		is_invalid;

	is_invalid = FALSE;
	i = 1;
	if (ft_isalpha(*name) == FALSE && *name != '_')
		return (TRUE);
	while (name[i])
	{
		if (ft_isalnum(name[i]) == FALSE && name[i] != '_')
		{
			is_invalid = TRUE;
			break ;
		}
		i++;
	}
	return (is_invalid);
}

/**
 * @brief Checks if the name and value are valid.
 * 
 * @param name variable name
 * @param value variable value
 * @return TRUE if name and value are valid, FALSE otherwise
 */
static int	valid_var(char *name, char *value)
{
	int	is_valid;

	if (invalid_name(name) == TRUE)
	{		
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		is_valid = FALSE;
	}
	else
	{
		if (value == NULL)
			is_valid = FALSE;
		else
			is_valid = TRUE;
	}
	return (is_valid);
}

/**
 * @brief Simulates export shell builtin, that adds a new variable at
 * environment variables list.
 * 
 * @param env_list environment variables list
 * @param var variable to be appended at environment variables list
 * @return void
 */
void	export(t_var *env_list, char **var)
{
	char	**key;
	char	*name;
	char	*value;
	size_t	i;

	i = 0;
	while (var[i] != NULL)
	{
		value = ft_strchr(var[i], '=');
		key = ft_split(var[i], '=');
		if (*key == NULL && value != NULL)
			name = value;
		else
			name = key[0];
		if (valid_var(name, value) == TRUE)
			new_variable(&env_list, name, ++value);
		ft_free(key);
		i++;
	}
}
