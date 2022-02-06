/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:08 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 09:11:19 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_status;

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
