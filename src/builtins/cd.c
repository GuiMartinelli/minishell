/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2022/02/03 19:39:01 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_directory(char *str)
{
	if (!str || chdir(str))
	{
		perror("chdir() failed");
		g_error_status = 1;
		return ;
	}
}

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
	char	*temp;

	temp = NULL;
	if (dir == NULL || (*dir == '-' && *(dir + 1) == '-' && *(dir + 2) == 0))
		temp = get_var_value("HOME", env_list);
	else if (*dir == '-' && *(dir + 1) == '\0')
	{
		temp = get_var_value("OLDPWD", env_list);
		ft_putendl_fd(dir, 1);
	}
	if (temp)
		change_directory(temp);
	else
		change_directory(dir);
	oldpwd = get_var_value("PWD", env_list);
	update_var(env_list, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_var(env_list, "PWD", pwd);
	free_n_null(oldpwd);
	free_n_null(pwd);
	free_n_null(temp);
}
