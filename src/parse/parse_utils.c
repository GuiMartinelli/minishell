/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:21:09 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/27 10:19:58 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	mv_ptr(char mode, char *str)
{
	int	x;

	x = 0;
	if (mode == '$')
	{
		x++;
		while ((ft_isalnum(str[x]) || str[x] == '_') && str[x])
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

size_t	comp_size(char *str1, char *str2)
{
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 > size2)
		return (size1);
	else
		return (size2);
}