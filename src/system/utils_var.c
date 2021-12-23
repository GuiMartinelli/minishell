/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:54:38 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/23 09:20:11 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	strlenchr(char	*s, char c)
{
	int	size;

	size = 0;
	while (s[size] != c && s[size] != '\0')
	{
		size++;
	}
	size++;
	return (size);
}

char	*str_cpy(char *src, char *dest, char c)
{
	while (*src != c && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	if (!*src)
		return (src);
	src++;
	return (src);
}

/**
 * @brief Split a string in two, before and after a char. Splits only in
 * the first occurrence of the char, because some variables may contain
 * several '=' in it's value.
 * 
 * @param s string to be splitted
 * @param c character to split, usually '='
 * @return returns a matrix containing the two splitted pieces of the string
 */
char	**ft_split_value(char const *s, char c)
{
	char	**ptr;
	int		cont;
	int		size;

	cont = 0;
	ptr = malloc(3 * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (cont < 2 && *s)
	{
		if (*s == c)
			s++;
		else
		{
			size = strlenchr((char *)s, c);
			ptr[cont] = (char *)malloc(size * sizeof(char));
			s = str_cpy((char *)s, ptr[cont], c);
			cont++;
			c = '\0';
		}
	}
	ptr[cont] = '\0';
	return (ptr);
}

char	*get_var_value(char *name, t_var *var_list)
{
	if (!name)
		return (NULL);
	while (var_list)
	{
		if (ft_strncmp(var_list->name, name, ft_strlen(name)) == 0)
			return (var_list->value);
		var_list = var_list->next;
	}
	return (NULL);
}
