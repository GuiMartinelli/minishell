/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:22:37 by proberto          #+#    #+#             */
/*   Updated: 2022/01/12 19:55:51 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle the SIGINT (CTRL + C) signal and redisplay the prompt.
 * 
 * @param signal signal number
 * @return void
 */
void	sig_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
