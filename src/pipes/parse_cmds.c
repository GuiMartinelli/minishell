/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/02 18:32:55 by proberto         ###   ########.fr       */
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
	while (*path)
		path++;
	while (*path != '/')
		path--;
	return (ft_strdup((path + 1)));
}

char	**parse_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list)
{
	char	**paths;
	char	**aux;
	int		index;

	if (**matrix == '|')
	{
		g_error_status = 1;
		write(2, "bash: syntax error near unexpected token `|'\n", 47);
		return (NULL);
	}
	aux = matrix;
	while (*matrix && (**matrix == '<' || **matrix == '>'))
		matrix += 2;
	index = 0;
	paths = parse_paths(env_list);
	cmd->name = check_path(paths, *matrix);
	cmd->option = ft_calloc(get_args_size(matrix), sizeof(char *));
	while (*matrix && **matrix != '|' && **matrix != '<' && **matrix != '>' )
	{
		cmd->option[index] = *matrix;
		matrix++;
		index++;
	}
	cmd->env = env;
	if (paths)
		free_matrix(paths);
	if (*aux && (**aux == '<' || **aux == '>'))
		return (aux);
	return (matrix);
}
