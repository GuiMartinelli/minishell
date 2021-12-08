/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2021/12/08 08:06:03 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sig_handler(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*cmd;
	t_var	*env_list;
	t_var	*curr;

	env_list = env_variables(envp);
	env(env_list, 1);
	// while (1)
	// {
	// 	prompt = new_prompt();
	// 	signal(SIGINT, sig_handler);
	// 	cmd = readline(prompt);
	// 	free(prompt);
	// 	if (cmd == NULL)
	// 		break ;
	// 	add_history(cmd);
	// 	eval(cmd);
	// 	free(cmd);
	// }
	// if (cmd)
	// 	free(cmd);
	// rl_clear_history();
	curr = env_list;
	while (curr)
	{
		env_list = env_list->next;
		free_var(curr);
		curr = env_list;
	}
	return (0);
}
