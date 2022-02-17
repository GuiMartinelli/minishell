/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:30:26 by proberto          #+#    #+#             */
/*   Updated: 2022/02/17 18:51:27 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Free and set a pointer to NULL, very useful to save some lines.
 * 
 * @param ptr pointer to be freed
 * @return void
 */
void	free_n_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/**
 * @brief Free a char array and set it to NULL.
 * 
 * @param matrix char array to be freed
 * @return void
 */
void	free_matrix(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[x])
	{
		free_n_null(matrix[x]);
		x++;
	}
	free_n_null(matrix);
}

/**
 * @brief Free a t_var type of struct.
 * 
 * @param var t_var struct to be freed
 * @return void
 */
void	free_var(t_var *var)
{
	free_n_null(var->name);
	free_n_null(var->value);
	var->next = NULL;
	free_n_null(var);
}

/**
 * @brief Free a t_env type of struct.
 * 
 * @param var_list variable list to be freed
 * @return void
 */
void	free_var_list(t_var *var_list)
{
	t_var	*curr;

	curr = var_list;
	while (curr)
	{	
		var_list = var_list->next;
		free_var(curr);
		curr = var_list;
	}
}

/**
 * @brief Open a execve to free all memory in the child process.
 * 
 * @param status command status, received by the signal inputed
 */
void	free_here_docs(int status)
{
	char	**cmd;
	int		fd[2];

	if (status == 130)
		cmd = ft_split("/usr/bin/bash bash -c 'exit 130'", ' ');
	else
		cmd = ft_split("/usr/bin/ls ls", ' ');
	pipe(fd);
	dup2(fd[1], 1);
	dup2(fd[1], 2);
	execve(cmd[0], &cmd[1], NULL);
}
