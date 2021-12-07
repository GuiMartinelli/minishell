/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 08:47:33 by guferrei          #+#    #+#             */
/*   Updated: 2021/12/07 20:40:38 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*check_path(char **env_path, char *cmd)
{
	char	*path;
	char	*temp;
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
