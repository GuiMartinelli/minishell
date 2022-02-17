/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:58:44 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/17 19:29:33 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Count the number of args that the command will get.
 * 
 * @param matrix matrix to check
 * @return int number of args
 */
static int	get_args_size(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[x] && !command_args_delimiter(matrix[x]))
			x++;
	return (x + 1);
}

/**
 * @brief Checks if the is a argument, pipe or redirect.
 * 
 * @param str string to check
 * @return int returns 1 if is a pipe or redirect, or 0 if isn't
 */
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

/**
 * @brief Check if pipe have syntax error
 * 
 * @param first_chr character to check
 * @return int 0 is there's error or 1 if there's no error
 */
static int	check_pipe_error(char first_chr)
{
	if (first_chr == '|')
	{
		g_error_status = 1;
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

/**
 * @brief Writes the data on the struct.
 * 
 * @param cmd struct to populate
 * @param cl matrix to format
 * @param env_list linked list of program variables
 * @return char** matrix position after parse
 */
static char	**write_cmd(t_cmd *cmd, char **cl, t_var *env_list)
{
	int		index;
	char	**paths;

	index = 0;
	paths = parse_paths(env_list);
	cmd->path = check_path(paths, *cl);
	if (cmd->path == NULL)
		cmd->path = ft_strdup(*cl);
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

/**
 * @brief Formats a matrix in a t_cmd struct, containing all useful
 * data to run in.
 * 
 * @param cmd struct of command data
 * @param cl matrix to format
 * @param env_list linked list of program variables
 * @return char** matrix position after parse
 */
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
