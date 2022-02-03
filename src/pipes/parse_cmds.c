/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/03 10:03:44 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_size(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[x] && !command_args_delimiter(matrix[x]))
			x++;
	return (x + 1);
}

int	command_args_delimiter(char *str)
{
	if (*str == '<' || *str == '>')
	{
		if (ft_strlen(str) == 1)
			return (1);
		else if (ft_strlen(str) == 2 && (*(str + 1) == *str))
			return (1);
		else
			return (0);
	}
	else if (*str == '|' && ft_strlen(str) == 1)
		return (1);
	else
		return (0);
}

int	check_pipe_error(char first_chr)
{
	if (first_chr == '|')
	{
		g_error_status = 1;
		write(2, "bash: syntax error near unexpected token `|'\n", 47);
		return (0);
	}
	return (1);
}

char	**write_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list)
{
	int		index;
	char	**paths;

	index = 0;
	paths = parse_paths(env_list);
	cmd->name = check_path(paths, *matrix);
	cmd->option = ft_calloc(get_args_size(matrix), sizeof(char *));
	while (*matrix && !command_args_delimiter(*matrix))
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

char	**parse_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list)
{
	char	**aux;

	if (!check_pipe_error(**matrix))
		return (NULL);
	aux = matrix;
	while (*matrix && (**matrix == '<' || **matrix == '>'))
	{
		matrix ++;
		if (*matrix)
			matrix++;
	}
	if (!*matrix)
		return (aux);
	matrix = write_cmd(cmd, matrix, env, env_list);
	if (*aux && (**aux == '<' || **aux == '>'))
		return (aux);
	return (matrix);
}
