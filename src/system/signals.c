/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:22:37 by proberto          #+#    #+#             */
/*   Updated: 2022/02/06 08:38:28 by proberto         ###   ########.fr       */
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
	g_error_status = 130;
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
	g_error_status = 130;
	write(1, "\n", 1);
}

/**
 * @brief Handle the SIGQUIT signal (CTRL + \) and exit the process.
 * 
 * @param signal signal number
 * @return void
 */
void	interrupt_here_docs(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(130);
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
	g_error_status = 131;
	ft_putendl_fd("Quit (core dumped)", 1);
}

/**
 * @brief Define signal handlers for SIGINT and SIGQUIT signals
 * 
 * @return void
 */
void	define_signal(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
