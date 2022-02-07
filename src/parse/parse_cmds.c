/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/06 21:17:38 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_args_size(char **matrix)
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

static int	check_pipe_error(char first_chr)
{
	if (first_chr == '|')
	{
		g_error_status = 1;
		write(2, "bash: syntax error near unexpected token `|'\n", 47);
		return (0);
	}
	return (1);
}

static char	**write_cmd(t_cmd *cmd, char **cl, t_var *env_list)
{
	int		index;
	char	**paths;

	index = 0;
	paths = parse_paths(env_list);
	cmd->path = check_path(paths, *cl);
	cmd->arg = ft_calloc(get_args_size(cl), sizeof(char *));
	while (*cl && !command_args_delimiter(*cl))
	{
		cmd->arg[index] = *cl;
		cl++;
		index++;
	}
	cmd->arg[index] = NULL;
	if (paths)
		free_matrix(paths);
	return (cl);
}

char	**parse_cmd(t_cmd *cmd, char **cl, t_var *env_list)
{
	char	**aux;

	if (!check_pipe_error(**cl))
		return (NULL);
	aux = cl;
	while (*cl && (**cl == '<' || **cl == '>'))
	{
		cl ++;
		if (*cl)
			cl++;
	}
	if (!*cl)
		return (aux);
	cl = write_cmd(cmd, cl, env_list);
	if (*aux && (**aux == '<' || **aux == '>'))
		return (aux);
	return (cl);
}
