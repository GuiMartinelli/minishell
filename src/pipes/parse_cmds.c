/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/31 09:41:04 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_size(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[x] && *matrix[x] != '|'
		&& *matrix[x] != '<' && *matrix[x] != '>' )
			x++;
	return (x + 1);
}

char	*parse_absolute_path(char *path)
{
	int		size;

	size = 0;
	while (*path)
		path++;
	while (*path != '/')
	{
		path--;
		size++;
	}
	return (ft_strdup((path + 1)));
}

char	**parse_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list)
{
	char	**paths;
	int		index;

	if (**matrix == '|')
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 47);
		return (NULL);
	}
	index = 0;
	paths = parse_paths(env_list);
	cmd->name = check_path(paths, matrix[0]);
	cmd->option = malloc(get_args_size(matrix) * sizeof(char *));
	while (*matrix && **matrix != '|' && **matrix != '<' && **matrix != '>' )
	{
		if (index == 0 && **matrix == '/')
			cmd->option[index] = parse_absolute_path(*matrix);
		else
			cmd->option[index] = *matrix;
		matrix++;
		index++;
	}
	cmd->option[index] = NULL;
	cmd->env = env;
	if (paths)
		free_matrix(paths);
	return (matrix);
}
