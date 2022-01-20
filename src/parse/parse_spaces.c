/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:11:48 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/20 08:54:00 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_quote(char *ptr, char quotes)
{
	if (*ptr != quotes && quotes)
		return (quotes);
	if (quotes == *ptr)
		return (0);
	else
		return (*ptr);
}

int	get_size(char *str)
{
	int		count;
	char	quotes;

	count = 0;
	quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			quotes = check_quote(str, quotes);
		else if ((*str == '|' || *str == '>' || *str == '<')
			&& !quotes && (*(str - 1) != ' ' || *(str + 1) != ' '))
		{
			count += 2;
			if (*str == *(str + 1))
			{
				str++;
				count++;
			}
		}
		count++;
		str++;
	}
	return (count);
}

char	*cpy_str(char *src, char *dest, char quotes)
{
	int		index;

	index = 0;
	while (*src)
	{
		if ((*src == '|' || *src == '<'
				|| *src == '>') && !quotes)
		{
			dest[index++] = ' ';
			dest[index++] = *src;
			if (*src == *(src + 1))
				dest[index++] = *src++;
			dest[index] = ' ';
		}
		else
		{
			if (*src == '"' || *src == '\'')
				quotes = check_quote(src, quotes);
			dest[index] = *src;
		}
		src++;
		index++;
	}
	return (dest);
}

char	*parse_spaces(char *str)
{
	char	*parsed;
	int		size;
	char	quotes;

	quotes = 0;
	size = get_size(str);
	if (size == (int)ft_strlen(str))
		return (str);
	parsed = ft_calloc(size, sizeof(char));
	if (!parsed)
		return (NULL);
	parsed = cpy_str(str, parsed, quotes);
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (parsed);
}
