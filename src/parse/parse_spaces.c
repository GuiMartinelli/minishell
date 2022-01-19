/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:11:48 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/19 20:17:56 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_size(char *str)
{
	int		count;
	char	quotes;

	count = 0;
	quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			if (quotes == *str)
				quotes = 0;
			else
				quotes = *str;
		}
		else if ((*str == '|' || *str == '>' || *str == '<') && !quotes)
		{
			count += 2;
			if (*str == *(str + 1))
			{
				str++;
				count += 2;
			}
		}
		count++;
		str++;
	}
	return (count);
}

char	*cpy_str(char *src, char *dest)
{
	int		index1;
	int		index2;
	char	quotes;

	quotes = 0;
	index1 = 0;
	index2 = 0;
	while (src[index1])
	{
		if ((src[index1] == '|' || src[index1] == '<'
				|| src[index1] == '>') && !quotes)
		{
			dest[index2] = ' ';
			index2++;
			dest[index2] = src[index1];
			index2++;
			if (src[index1] == src[index1 + 1])
			{
				dest[index2] = src[index1];
				index1++;
				index2++;
			}
			dest[index2] = ' ';
		}
		else
		{
			if (src[index1] == '"' || src[index1] == '\'')
			{
				if (quotes)
					quotes = 0;
				else
				quotes = src[index1];
			}
			dest[index2] = src[index1];
		}
		index2++;
		index1++;
	}
	dest[index2] = '\0';
	return (dest);
}

char	*parse_spaces(char *str)
{
	char	*parsed;
	int		size;
	
	size = get_size(str);
	if (size == (int)ft_strlen(str))
		return (str);
	parsed = malloc(size * sizeof(char));
	if (!parsed)
		return (NULL);
	parsed = cpy_str(str, parsed);
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (parsed);
}
