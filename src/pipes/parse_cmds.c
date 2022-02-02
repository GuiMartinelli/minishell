/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/02 12:23:10 by guferrei         ###   ########.fr       */
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

char	**solve_redirects(char **splitted)
{
	int		index;
	char	*redirect;
	char	*file;

	index = 0;
	if ((**splitted == '<' || **splitted == '>') && splitted[index + 2])
	{
		redirect = splitted[0];
		file = splitted[1];
		while (splitted[index + 2] && *splitted[index + 2] != '|')
		{
			splitted[index] = splitted[index + 2];
			index++;
		}
		splitted[index] = redirect;
		splitted[index + 1] = file;
	}
	if ((**splitted == '<' || **splitted == '>') && splitted[index + 2])
		splitted = solve_redirects(splitted);
	return (splitted);
}

char	**parse_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list)
{
	char	**paths;
	int		index;

	if (**matrix == '|')
	{
		g_error_status = 1;
		write(2, "bash: syntax error near unexpected token `|'\n", 47);
		return (NULL);
	}
	index = 0;
	matrix = solve_redirects(matrix);
	paths = parse_paths(env_list);
	cmd->name = check_path(paths, matrix[0]);
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
	return (matrix);
}
