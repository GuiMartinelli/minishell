/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:24:42 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 15:58:28 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_variable(char *c, char quote)
{
	if (*c == '~' && (*(c - 1) == ' ' && (!*(c + 1)
				|| *(c + 1) == ' ' || *(c + 1) == '/')) && !quote)
		return (1);
	if (*c == '$' && (*(c + 1) == '_' || ft_isalnum(*(c + 1))
			|| *(c + 1) == '?') && quote != '\'')
		return (1);
	else
		return (0);
}

static char	*get_var_name(char *str)
{
	int		index;
	int		size;
	char	*name;

	index = 0;
	size = 0;
	while (str[index] != '$' && str[index])
		index++;
	index++;
	while (ft_isalnum(str[index]) || str[index] == '_' || str[index] == '?')
	{
		index++;
		size++;
	}
	name = malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str + (index - size), size + 1);
	return (name);
}

int	get_var_size(char *str, t_var *env, char **env_matrix)
{
	char	*name;
	char	*value;
	int		size;

	if (*str == '~')
		return (home_size(env_matrix));
	if (*str == '?')
	{
		value = ft_itoa(g_error_status);
		size = (int)ft_strlen(value);
		free_n_null(value);
		return (size);
	}
	name = get_var_name(str);
	size = 0;
	value = hash_table(name, env);
	if (!value)
		size = 0;
	else
		size = ft_strlen(value);
	free_n_null(name);
	free_n_null(value);
	return (size);
}

int	var_value_cpy(char *dest, char *src, t_var *env, char **env_matrix)
{
	char	*name;
	char	*value;
	int		cpy_size;

	if (src[0] == '~')
	{
		value = home_value(env_matrix);
		cpy_size = ft_strlcpy(dest, value, (ft_strlen(value) + 1));
		return (cpy_size);
	}
	else
		name = get_var_name(src);
	value = hash_table(name, env);
	if (name)
	{
		free(name);
		name = NULL;
	}
	if (!value)
		return (0);
	cpy_size = ft_strlcpy(dest, value, (ft_strlen(value) + 1));
	free_n_null(value);
	return (cpy_size);
}
