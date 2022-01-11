/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:24:42 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/11 16:40:33 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str)
{
	int		index;
	int		size;
	char	*name;

	index = 0;
	size = 0;
	while (str[index] != '$' && str[index])
		index++;
	index++;
	while (ft_isalnum(str[index]) || str[index] == '_')
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

int	get_var_size(char *str, t_var *env, t_var *local)
{
	char	*name;
	char	*value;
	int		size;

	name = get_var_name(str);
	size = 0;
	value = get_var_value(name, env);
	if (!value)
		value = get_var_value(name, local);
	if (!value)
		size = 0;
	else
		size = ft_strlen(value);
	if (name)
	{
		free(name);
		name = NULL;
	}
	return (size);
}

int	var_value_cpy(char *dest, char *src, t_var *env, t_var *local)
{
	char	*name;
	char	*value;
	int		cpy_size;

	(void)local;
	if (src[0] == '~')
		name = ft_strdup("HOME");
	else
		name = get_var_name(src);
	value = get_var_value(name, env);
	if (name)
	{
		free(name);
		name = NULL;
	}
	if (!value)
		return (0);
	cpy_size = ft_strlcpy(dest, value, (ft_strlen(value) + 1));
	return (cpy_size);
}
