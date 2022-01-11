/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:08:25 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/11 16:37:44 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int	matrix_size(char *s)
{
	int		count;
	char	quote;

	count = 0;
	while (*s)
	{
		if ((*s == '"' || *s == '\'') && is_quotes(s, *s))
		{
			count++;
			quote = *s++;
			while (*s != quote)
				s++;
			s++;
		}
		else if (*s != ' ')
		{
			count++;
			while (*s != ' ' && *s != '\0')
				s++;
		}
		else if (*s == ' ')
			s++;
	}
	count++;
	return (count);
}

int	strlenchr_split(char	*s, char c)
{
	int		size;

	size = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		size++;
	}
	size++;
	return (size);
}

char	*str_cpy_split(char *src, char *dest, char c)
{
	while (*src != c && *src != '\0')
	{
		if (*src == '\\')
			src++;
		else
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	*dest = '\0';
	if (*src == '\0')
		return (src);
	src++;
	return (src);
}

char	*alloc_n_copy(char *s, char c, int index, char **dest)
{
	int	size;

	if (c == '"' || c == '\'')
		s++;
	size = strlenchr_split((char *)s, c);
	dest[index] = (char *)malloc(size * sizeof(char));
	if (!dest[index])
		return (NULL);
	return (str_cpy_split((char *)s, dest[index], c));
}

char	**ft_split_string(char *s)
{
	int		str;
	char	**ptr;
	int		cont;

	cont = 0;
	str = matrix_size(s);
	ptr = malloc(str * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (cont < (str - 1))
	{
		if (*s == ' ' || *s == '\\')
			s++;
		else
		{
			if ((*s == '"' || *s == '\'') && is_quotes(s, *s)
				&& *(s - 1) != '\\')
				s = alloc_n_copy(s, *s, cont, ptr);
			else
				s = alloc_n_copy(s, ' ', cont, ptr);
			cont++;
		}
	}
	ptr[cont] = (char *) NULL;
	return (ptr);
}
