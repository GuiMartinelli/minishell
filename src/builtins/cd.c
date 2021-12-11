/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2021/12/10 21:43:28 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Changes the current working directory.
 * 
 * @param dir the destination directory to change to
 * @param env_list the environment variables list
 * @return void
 */
void	cd(char *dir, t_var *env_list)
{
	char	*pwd;
	char	*oldpwd;

	if (chdir(dir))
	{
		perror("chdir() failed");
		return ;
	}
	oldpwd = get_var_value("PWD", env_list);
	update_var(env_list, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_var(env_list, "PWD", pwd);
	free(pwd);
}
