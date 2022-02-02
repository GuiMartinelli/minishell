/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2022/02/02 11:23:55 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Simulates the shell's built-in cd, which changes the current 
 * working directory.
 * 
 * @param dir the destination directory to change to
 * @param env_list the environment variables list
 * @return void
 */
void	cd(char *dir, t_var *env_list)
{
	char	*pwd;
	char	*oldpwd;

	if (dir == NULL || (*dir == '-' && *(dir + 1) == '-' && *(dir + 2) == 0))
		dir = get_var_value("HOME", env_list);
	else if (*dir == '-' && *(dir + 1) == '\0')
	{
		dir = get_var_value("OLDPWD", env_list);
		ft_putendl_fd(dir, 1);
	}
	if (chdir(dir))
	{
		perror("chdir() failed");
		g_error_status = 1;
		return ;
	}
	oldpwd = get_var_value("PWD", env_list);
	update_var(env_list, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_var(env_list, "PWD", pwd);
	free(pwd);
}
