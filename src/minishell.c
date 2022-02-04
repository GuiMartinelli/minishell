/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2022/02/04 11:37:58 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_status;

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*cmd;
	t_var	*env_list;

	(void)argc;
	(void)argv;
	env_list = env_variables(envp);
	while (1)
	{
		prompt = new_prompt();
		signal(SIGINT, redisplay_prompt);
		signal(SIGQUIT, SIG_IGN);
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
	free_var_list(env_list);
	return (0);
}
