/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:39:20 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 21:48:46 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Print error message.
 * 
 * @return int 
 */
static int	error_flags(void)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	g_error_status = 1;
	return (-1);
}

/**
 * @brief Try to change the current directory to the given path.
 * 
 * @param dir the directory to change to
 * @return int 
 */
static int	change_directory(char *dir)
{
	if (!dir || chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (dir)
			perror(dir);
		else
			perror(" ");
		g_error_status = 1;
		return (-1);
	}
	return (1);
}

/**
 * @brief cd subfunction
 * 
 * @param temp possible path (home or oldpwd)
 * @param aux auxiliary variable for directory
 * @param env_list environment variables list
 * @return void
 */
static void	cd_sub(char *temp, char *aux, t_var *env_list)
{
	char	*pwd;
	char	*oldpwd;

	if (temp)
		change_directory(temp);
	else
		change_directory(aux);
	oldpwd = hash_table("PWD", env_list);
	update_var(env_list, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_var(env_list, "PWD", pwd);
	free_n_null(oldpwd);
	free_n_null(pwd);
	free_n_null(temp);
}

/**
 * @brief Simulates the shell's built-in cd, which changes the current 
 * working directory.
 * 
 * @param dir the destination directory to change to
 * @param env_list the environment variables list
 * @return int
 */
int	cd(char **dir, t_var *env_list)
{
	char	*temp;
	char	*aux;

	temp = NULL;
	aux = *dir++;
	if (!aux || (*aux == '-' && *(aux + 1) == '-' && *(aux + 2) == '\0'))
	{
		if (aux && *dir)
			return (change_directory(*dir));
		temp = hash_table("HOME", env_list);
	}
	else if (*aux == '-' && *(aux + 1) == '\0')
	{
		if (aux && *dir)
			return (error_flags());
		temp = hash_table("OLDPWD", env_list);
		ft_putendl_fd(temp, 1);
	}
	if (aux && *dir)
		return (error_flags());
	cd_sub(temp, aux, env_list);
	return (1);
}
