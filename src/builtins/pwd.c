/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:03:12 by proberto          #+#    #+#             */
/*   Updated: 2021/11/29 15:06:54 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	return (tmp);
}

void	pwd(void)
{
	char	*pwd;
	size_t	len;

	pwd = get_pwd();
	len = ft_strlen(pwd);
	write(1, pwd, len);
	write(1, "\n", 1);
	free(pwd);
}
