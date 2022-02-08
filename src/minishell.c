/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 15:50:06 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_status;

/**
 * @brief Main function of the minishell.
 * 
 * @param argc number of arguments passed to the program
 * @param argv array of arguments passed to the program
 * @param envp environment variables passed to the program
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_env_var	env;

	(void)argc;
	(void)argv;
	env.list = env_variables(envp);
	env.envp = envp;
	repl(&env);
	free_var_list(env.list);
	return (0);
}
