/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 15:58:17 by proberto         ###   ########.fr       */
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
		temp = hash_table("HOME", env_list);
	else if (*dir == '-' && *(dir + 1) == '\0')
	{
		temp = hash_table("OLDPWD", env_list);
		ft_putendl_fd(dir, 1);
	}
	if (temp)
		change_directory(temp);
	else
		change_directory(dir);
	oldpwd = hash_table("PWD", env_list);
	update_var(env_list, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_var(env_list, "PWD", pwd);
	free_n_null(oldpwd);
	free_n_null(pwd);
	free_n_null(temp);
}
