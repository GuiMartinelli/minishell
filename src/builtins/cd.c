/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2021/11/30 17:17:22 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Changes the current working directory.
 * 
 * @todo update the PWD env variable
 * @param dir the destination directory to change to 
 * @return void
 */
void	cd(char *dir)
{
	char	*tmp;

	if (chdir(dir))
		perror("chdir() failed");
	tmp = getcwd(NULL, 0);
	setenv("PWD", tmp, 1);
	free(tmp);
}
