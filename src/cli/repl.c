/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:56:05 by proberto          #+#    #+#             */
/*   Updated: 2022/02/10 21:26:03 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the user name from the system.
 * 
 * @param envp environment variables passed to the program
 * @return char* 
 */
static char	*get_user(char **envp)
{
	char	*user;

	user = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "USER", ft_strlen("USER")) == 0)
			user = ft_strnstr(*envp, "=", ft_strlen(*envp));
		envp++;
	}
	if (user)
		user++;
	if (!user)
		user = "Minishell";
	return (user);
}

/**
 * @brief Receive input from a single user, execute them and return the result 
 * to the user (repl acronym for read-eval-print loop).
 * 
 * @param env structure containing the environment variables (list and envp)
 * @return void
 */
void	repl(t_env_var *env)
{
	char	*prompt;
	char	*cl;
	char	*user;

	user = get_user(env->envp);
	while (TRUE)
	{
		prompt = new_prompt(user);
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
