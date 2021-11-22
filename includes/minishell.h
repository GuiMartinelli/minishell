/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:14 by proberto          #+#    #+#             */
/*   Updated: 2021/11/22 11:44:08 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0

typedef struct s_prompt
{
	char	*prompt;
	char	*pwd;
	char	*target;
	char	*prefix_color;
	char	*suffix_color;
	size_t	len;
}			t_prompt;

char	*get_pwd(void);
char	*new_prompt(void);

#endif
