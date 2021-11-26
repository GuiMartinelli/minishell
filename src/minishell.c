/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2021/11/22 12:33:18 by proberto         ###   ########.fr       */
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

int	main(void)
{
	char	*prompt;
	char	*cmd;

	while (1)
	{
		prompt = new_prompt();
		signal(SIGINT, sig_handler);
		cmd = readline(prompt);
		printf("\ncommand: %s\n", cmd);
		free(prompt);
		if (cmd == NULL)
			break ;
		add_history(cmd);
		free(cmd);
	}
	if (cmd)
		free(cmd);
	rl_clear_history();
	return (0);
}
