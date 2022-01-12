/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:03:12 by proberto          #+#    #+#             */
/*   Updated: 2022/01/12 18:07:12 by proberto         ###   ########.fr       */
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
 * @brief Simulates the shell's built-in pwd, which prints the current working 
 * directory.
 * 
 * @param fd the file descriptor to print
 * @return void
 */
void	pwd(int fd)
{
	char	*pwd;

	pwd = get_pwd();
	ft_putendl_fd(pwd, fd);
	free(pwd);
}
