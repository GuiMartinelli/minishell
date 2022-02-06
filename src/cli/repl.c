/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:56:05 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 09:02:55 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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