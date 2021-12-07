/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:49:10 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/07 20:39:52 by proberto         ###   ########.fr       */
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

char	**ft_split_value(char const *s, char c)
{
	char	**ptr;
	int		cont;
	int		size;

	cont = 0;
	ptr = malloc(3 * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (cont < 2 && s)
	{
		if (*s == c)
			s++;
		else
		{
			size = strlenchr((char *)s, c);
			ptr[cont] = (char *)malloc(size * sizeof(char));
			s = str_cpy((char *)s, ptr[cont], c);
			cont++;
		}
	}
	ptr[cont] = (char *) NULL;
	return (ptr);
}
