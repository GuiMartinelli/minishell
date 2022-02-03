/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 08:47:33 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/31 11:45:23 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Search for PATH environment variable, and parse it in a new matrix.
 * 
 * @param env environment variables matrix, usually received at main function
 * @return matrix containing all environment paths
 */
char	**parse_paths(t_var *env_list)
{
	t_var	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strncmp(curr->name, "PATH", 4))
			return (ft_split(curr->value, ':'));
		else
			curr = curr->next;
	}
	return (NULL);
}

/**
 * @brief Join a path and a command in a string.
 * 
 * @param env_path path of the command
 * @param cmd command to be executed
 * @return string created
 */
char	*build_path(char *env_path, char *cmd)
{
	char	*path;
	char	*temp;

	path = NULL;
	path = ft_strdup(env_path);
	temp = path;
	path = ft_strjoin(path, "/");
	free(temp);
	temp = path;
	path = ft_strjoin(path, cmd);
	free(temp);
	return (path);
}

/**
 * @brief Check each environment path with a command, to find where the command
 * is installed.
 * 
 * @param env_path matrix that contains all environment paths
 * @param cmd command to search for
 * @return returns the right path of the command, or NULL if the command
 * doesn't exist or something fails
 */
char	*check_path(char **env_path, char *cmd)
{
	char	*path;
	int		index;

	index = 0;
	path = NULL;
	if (!env_path)
		return (NULL);
	if (*cmd == '/')
		return (ft_strdup(cmd));
	while (env_path[index])
	{
		path = build_path(env_path[index], cmd);
		if (!*path)
			return (NULL);
		if (!access(path, F_OK))
			return (path);
		else
		{
			free_n_null(path);
			index++;
		}
	}
	return (NULL);
}
