/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/18 20:18:48 by proberto         ###   ########.fr       */
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

char	**parse_cmd(t_cmd *cmd, char **matrix, char **env)
{
	char	**paths;
	int		index;

	index = 0;
	paths = parse_paths(env);
	cmd->name = check_path(paths, matrix[0]);
	cmd->option = malloc(get_args_size(matrix) * sizeof(char *));

	while (*matrix && **matrix != '|' && **matrix != '<' && **matrix != '>' )
	{
		cmd->option[index] = *matrix;
		matrix++;
		index++;
	}
	cmd->option[index] = NULL;
	cmd->env = env;
	free_matrix(paths);
	return (matrix);
}