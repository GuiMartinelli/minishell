/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:48:57 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 12:39:15 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks for a pipe on the command line.
 * 
 * @param cl char array (acronymous for command line)
 * @return True if there is a pipe, False if there is none or if there is a
 * double pipe (one pipe followed by another pipe)
*/
int	is_there_a_pipe(char **cl)
{
	while (*cl)
	{
		if (**cl == '|')
		{
			if (ft_strlen(*cl) > 1 || (*(++cl) && **cl == '|'))
				return (FALSE);
			return (TRUE);
		}
		cl++;
	}
	return (FALSE);
}

/**
 * @brief Checks for any redirects on the command line.
 * 
 * @param cl char array (acronymous for command line)
 * @param redirection the possible redirects to inputs (<, <<) and
 * outputs (>, >>)
 * @return True if there is a redirect, False otherwise
*/
int	is_there_redirections(char **cl, char redirection)
{
	while (*cl && **cl != '|')
	{
		if (**cl == redirection && ft_strlen(*cl) <= 2)
			return (TRUE);
		cl++;
	}
	return (FALSE);
}

void	free_cmd(t_cmd *cmd)
{
	free_n_null(cmd->arg);
	free_n_null(cmd->path);
}
