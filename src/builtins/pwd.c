/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:03:12 by proberto          #+#    #+#             */
/*   Updated: 2021/12/09 15:05:38 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Gets the current working directory.
 * 
 * @return char* pointer to the current working directory
 */
char	*get_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	return (tmp);
}

/**
 * @brief Prints the current working directory.
 * 
 * @return void
 */
void	pwd(int fd)
{
	char	*pwd;

	pwd = get_pwd();
	ft_putendl_fd(pwd, fd);
	free(pwd);
}
