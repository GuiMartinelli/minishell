/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2021/12/22 15:38:31 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*cmd;
	t_var	*env_list;

	env_list = env_variables(envp);
	while (1)
	{
		prompt = new_prompt();
		signal(SIGINT, sig_handler);
		cmd = readline(prompt);
		free(prompt);
		if (cmd == NULL)
			break ;
		add_history(cmd);
		eval(cmd, env_list, envp);
		free(cmd);
	}
	if (cmd)
		free(cmd);
	rl_clear_history();
	// env(env_list, 1);
	free_var_list(env_list);
	return (0);
}
