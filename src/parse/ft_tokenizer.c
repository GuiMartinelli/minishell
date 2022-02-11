/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:08:25 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/11 16:42:17 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

static int	matrix_size(char *s)
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

static int	strlenchr_split(char	*s, char c)
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

static char	*str_cpy_split(char *src, char *dest, char c)
{
	int	sinalize;

	sinalize = check_special_chars(src, c);
	while (*src != c && *src != '\0')
	{
		if ((*src == '"' || *src == '\'') && c == ' ')
			src = skip_chars(src);
		else
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	if (sinalize)
		*dest = 3;
	else
		*dest = '\0';
	if (*src == '\0')
		return (src);
	src++;
	return (src);
}

static char	*alloc_n_copy(char *s, char c, int index, char **dest)
{
	int	size;

	size = 0;
	if (c == '"' || c == '\'')
	{
		s++;
		if (check_special_chars(s, c))
			size = 1;
	}
	size += strlenchr_split((char *)s, c);
	dest[index] = (char *)ft_calloc(size, sizeof(char));
	if (!dest[index])
		return (NULL);
	return (str_cpy_split((char *)s, dest[index], c));
}

char	**ft_split_string(char *s)
{
	int		size;
	char	**ptr;
	int		cont;

	cont = 0;
	size = matrix_size(s);
	ptr = ft_calloc(size, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (cont < (size - 1))
	{
		if (*s == ' ')
			s++;
		else
		{
			if ((*s == '"' || *s == '\'') && is_quotes(s, *s))
				s = alloc_n_copy(s, *s, cont, ptr);
			else
				s = alloc_n_copy(s, ' ', cont, ptr);
			cont++;
		}
	}
	ptr[cont] = (char *) NULL;
	return (ptr);
}
