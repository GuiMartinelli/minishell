/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:21:09 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/17 19:43:18 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if the string contain closed quotation marks.
 * 
 * @param str string to check
 * @param q single quote or double quotation marks
 * @return int return 1 if true or 0 if false
 */
int	is_quotes(char *str, char q)
{
	while (*str)
	{
		if (*str == q)
		{
			str++;
			while (*str != q)
			{
				if (!*str)
					return (0);
				str++;
			}
			return (1);
		}
		str++;
	}
	return (0);
}

/**
 * @brief Move a pointer after a variable name, spaces in a row
 * or a quoted argument.
 * 
 * @param mode informs if is a variable name, spaces or quotation marks
 * @param str string to move the pointer
 * @return int number to increment to the pointer
 */
int	mv_ptr(char mode, char *str)
{
	int	x;

	x = 0;
	if (mode == '$')
	{
		x++;
		while ((ft_isalnum(str[x]) || str[x] == '_' || str[x] == '?') && str[x])
			x++;
	}
	else if (mode == ' ')
	{
		while (str[x + 1] == ' ' && str[x + 1])
			x++;
	}
	else if (mode == '~')
		x++;
	else if (mode == '\'' || mode == '"')
	{
		x++;
		while (str[x] != mode)
				x++;
		x++;
	}
	return (x);
}

/**
 * @brief Compares the size of two string and returns the longest.
 * 
 * @param str1 string number 1
 * @param str2 string number 2
 * @return size_t size of the longest string
 */
size_t	comp_size(char *str1, char *str2)
{
	size_t	size1;
	size_t	size2;

	size1 = 0;
	size2 = 0;
	if (str1)
		size1 = ft_strlen(str1);
	if (str2)
		size2 = ft_strlen(str2);
	if (size1 > size2)
		return (size1);
	else
		return (size2);
}

/**
 * @brief Gets the string lenght of HOME environment variable.
 * 
 * @param matrix matrix of Shell environment variables
 * @return int number of characters of HOME value
 */
int	home_size(char **matrix)
{
	while (ft_strncmp(*matrix, "HOME", 4))
		matrix++;
	return (((int)ft_strlen(*matrix) - 4));
}

/**
 * @brief Expands the value of HOME environment variable.
 * 
 * @param matrix matrix of Shell environment variables
 * @return char* expanded and allocated value of home
 */
char	*home_value(char **matrix)
{
	char	*value;

	while (ft_strncmp(*matrix, "HOME", 4))
		matrix++;
	value = (*matrix + 5);
	return (value);
}
