/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:55:52 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 12:12:31 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmd_struct(t_cmd *cmd)
{
	cmd->path = NULL;
	cmd->arg = NULL;
	cmd->read = STDIN_FILENO;
	cmd->write = STDOUT_FILENO;
}

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
	init_cmd_struct(&cmd);
	run_cl(&cmd, cl_lex, env);
	free_matrix(cl_lex);
}
