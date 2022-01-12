/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 08:47:33 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/12 19:42:25 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Search for PATH environment variable, and parse it in a new matrix.
 * 
 * @param env environment variables matrix, usually received at main function
 * @return matrix containing all environment paths
 */
char	**parse_paths(char **env)
{
	char	*ptr;
	int		index;

	index = 0;
	while (env[index])
	{
		if (!ft_strncmp(env[index], "PATH", 4))
		{
			ptr = env[index] + 5;
			return (ft_split(ptr, ':'));
		}
		else
			index++;
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
