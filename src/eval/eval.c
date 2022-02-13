/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/02/12 23:00:23 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check for syntax error (more than one pipe followed).
 * 
 * @param cl char array (acronym for command line)
 * @return true if there is a syntax error, false otherwise
 */
static int	check_syntax_error(char **cl)
{
	size_t	i;

	i = 0;
	while (cl[i])
	{
		if (ft_strchr(cl[i], '|')
			&& (cl[i + 1] && ft_strchr(cl[i + 1], '|')))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'",
				STDERR_FILENO);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/**
 * @brief Initialize the command structure.
 * 
 * @param cmd command structure to be initialized
 * @return void
 */
static void	init_cmd_struct(t_cmd *cmd)
{
	cmd->path = NULL;
	cmd->arg = NULL;
	cmd->read = STDIN_FILENO;
	cmd->write = STDOUT_FILENO;
}

/**
 * @brief Evaluate the command passed as an argument tokenize it and send it 
 * for execution.
 * 
 * @param cl char array (acronym for command line)
 * @param env structure containing the environment variables (list and envp)
 */
void	eval(char *cl, t_env_var *env)
{
	char	**cl_lex;
	t_cmd	cmd;

	cl_lex = ft_lexer(cl, env->list, env->envp);
	if (!*cl_lex)
	{
		free_matrix(cl_lex);
		return ;
	}
	if (check_syntax_error(cl_lex) == TRUE)
	{
		free_matrix(cl_lex);
		return ;
	}
	init_cmd_struct(&cmd);
	run_cl(&cmd, cl_lex, env);
	free_matrix(cl_lex);
}
