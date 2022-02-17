/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:36:26 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/17 19:39:04 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if the string is at the end of a quoted argument or at the
 * beggining
 * 
 * @param ptr string to check
 * @param quotes quotation marks
 * @return char returns 0 if quoted arguments ended, or the quotation marks if
 * it started
 */
char	check_quote(char *ptr, char quotes)
{
	if (*ptr != quotes && quotes)
		return (quotes);
	if (quotes == *ptr)
		return (0);
	else
		return (*ptr);
}

/**
 * @brief Check if pipes or redirects needs space around to be
 * correctly interpreted.
 * 
 * @param str string to check
 * @param index index of the string
 * @return int number of needed chars
 */
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

/**
 * @brief Write the quotes when necessary
 * 
 * @param src string to read
 * @param dest parsed string to copy
 * @param index actual index of the string
 * @return char quotation marks founded
 */
char	save_quotes(char *src, char *dest, int index)
{
	char	quotes;

	quotes = 0;
	if (*src == '"' || *src == '\'')
		quotes = check_quote(src, quotes);
	dest[index] = *src;
	return (quotes);
}

/**
 * @brief Adds space between pipe, to program interpret it right, if necessary.
 * 
 * @param src string to read
 * @param dest parsed string to write
 * @param quotes char which indicates if there is quotation marks
 * @param index actual index of the string
 * @return int index of the string after writing spaces
 */
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
