/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:36:26 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/03 20:37:09 by guferrei         ###   ########.fr       */
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

int	check_tokens(char *str, int index)
{
	int	count;

	count = 0;
	if (*str == '|')
	{
		if (index && *(str - 1) != ' ')
			count++;
		if (*(str + 1) && *(str + 1) != ' ')
			count++;
	}
	else if (*str == '>' || *str == '<')
	{
		if (index && *(str - 1) != ' ')
			count++;
		if (*(str + 1) && *(str + 1) != ' ')
			count++;
	}
	return (count);
}

char	save_quotes(char *src, char *dest, int index)
{
	char	quotes;

	quotes = 0;
	if (*src == '"' || *src == '\'')
		quotes = check_quote(src, quotes);
	dest[index] = *src;
	return (quotes);
}

int	solve_pipes(char *src, char *dest, char quotes, int index)
{
	if (*src == '|' && !quotes)
	{
		if (index > 0 && *(src - 1) != ' ')
			dest[index++] = ' ';
		dest[index] = *src;
		if (*(src + 1) && *(src + 1) != ' ')
			dest[++index] = ' ';
	}
	return (index);
}
