/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:11:48 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/03 20:38:23 by guferrei         ###   ########.fr       */
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
			quotes = check_quote(str, quotes);
		else if ((*str == '|' || *str == '>' || *str == '<') && !quotes)
			count += check_tokens(str, count);
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
		if ((*src == '<' || *src == '>') && !quotes)
		{
			if (index > 0 && *(src - 1) != ' ' && dest[index - 1] != ' ')
				dest[index++] = ' ';
			dest[index] = *src;
			if (*src == *(src + 1))
				dest[++index] = *src++;
			if (*(src + 1) && *(src + 1) != ' ')
				dest[++index] = ' ';
		}
		else if (*src == '|' && !quotes)
			index = solve_pipes(src, dest, quotes, index);
		else
			quotes = save_quotes(src, dest, index);
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
	parsed = ft_calloc((size + 1), sizeof(char));
	if (!parsed)
		return (NULL);
	parsed = cpy_str(str, parsed, quotes);
	free_n_null(str);
	return (parsed);
}
