/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:22:37 by proberto          #+#    #+#             */
/*   Updated: 2022/01/13 17:43:59 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle the SIGINT signal (CTRL + C), stop the process and 
 * redisplay the command prompt.
 * 
 * @param signal signal number
 * @return void
 */
void	redisplay_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Handle the SIGINT signal (CTRL + C) and stop the forked process.
 * 
 * @param signal signal number
 * @return void
 */
void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

/**
 * @brief Handle the SIGQUIT signal (CTRL + \) or (CTRL + ]), stop the forked 
 * process and generate a core dump.
 * 
 * @param signal signal number
 * @return void
 */
void	quit_process(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit (core dumped)", 1);
}
