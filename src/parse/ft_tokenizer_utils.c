/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:06:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/17 19:35:04 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Writes a [END OF TEXT] char at a pointer
 * 
 * @param dest pointer to write
 */
void	ft_sinalize(char *dest)
{
	while (dest)
		dest++;
	*dest = 3;
}

/**
 * @brief Checks if a character needs special treatment, like pipes or
 * redirects.
 * 
 * @param str pointer to a char to check
 * @param c char containing the quotation marks which involves the string, if
 * there is a quotation marks
 * @return int returns 0 string contains special chars, or 1 if it doesn't
 */
int	check_special_chars(char *str, char c)
{
	if (c != '"' && c != '\'')
		return (0);
	if (*str == '>' || *str == '<')
	{
		if ((str + 1) && *(str + 1) == c)
			return (1);
		if (*(str + 1) && *(str + 2)
			&& *(str + 1) == *str && *(str + 2) == c)
			return (1);
		else
			return (0);
	}
	if (*str == '|')
	{
		if ((str + 1) && *(str + 1) == c)
			return (1);
		else
			return (0);
	}
	return (0);
}

/**
 * @brief Skips specific chars to avoid writing it on parsed string
 * 
 * @param src pointer to a char
 * @return char* pointer to string after skipped char, or at same point
 * if isn't necessary to skip
 */
char	*skip_chars(char *src)
{
	static char	quote;

	if (quote != *src && is_quotes(src, *src))
	{
		quote = *src;
		src++;
		if (*src == *(src - 1))
		{
			src++;
			quote = 0;
		}
	}
	else if (quote == *src)
	{
		quote = 0;
		src++;
	}
	return (src);
}
