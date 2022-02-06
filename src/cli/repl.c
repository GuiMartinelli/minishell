/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:56:05 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 16:16:59 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Receive input from a single user, execute them and return the result 
 * to the user (repl acronym for read-eval-print loop).
 * 
 * @param env structure containing the environment variables (list and envp)
 * return void
 */
void	repl(t_env_var *env)
{
	char	*prompt;
	char	*cl;

	while (TRUE)
	{
		prompt = new_prompt();
		signal(SIGINT, redisplay_prompt);
		signal(SIGQUIT, SIG_IGN);
		cl = readline(prompt);
		free(prompt);
		if (cl == NULL)
			break ;
		add_history(cl);
		eval(cl, env);
		free(cl);
	}
	if (cl)
		free(cl);
	rl_clear_history();	
}