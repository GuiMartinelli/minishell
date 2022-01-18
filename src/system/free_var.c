/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:30:26 by proberto          #+#    #+#             */
/*   Updated: 2022/01/17 21:09:06 by guferrei         ###   ########.fr       */
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
