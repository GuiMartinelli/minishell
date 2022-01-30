/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by proberto          #+#    #+#             */
/*   Updated: 2022/01/26 15:24:45 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Calculate the length of the prompt string.
 * 
 * @param prompt prompt struct
 * @return total len of prompt
 */
static size_t	get_prompt_len(t_prompt *prompt)
{
	return (ft_strlen(prompt->pwd)
		+ ft_strlen(prompt->prefix_color)
		+ ft_strlen(prompt->suffix_color)
		+ ft_strlen(prompt->target)
		+ 1);
}

/**
 * @brief Concatenate strings that make up the prompt.
 * 
 * @param prompt prompt struct
 * @return void
 */
static void	build_prompt(t_prompt *prompt)
{
	ft_strlcat(prompt->prompt, prompt->prefix_color, prompt->len);
	ft_strlcat(prompt->prompt, prompt->pwd, prompt->len);
	ft_strlcat(prompt->prompt, prompt->suffix_color, prompt->len);
	ft_strlcat(prompt->prompt, prompt->target, prompt->len);
}

/**
 * @brief Responsible for creating the prompt string to be displayed in the 
 * CLI (command line interface).
 * 
 * @return the char* pointer to a new prompt
 */
char	*new_prompt(void)
{
	t_prompt	prompt;

	prompt.pwd = get_pwd();
	prompt.prefix_color = "\001\033[1;33m\002";
	prompt.suffix_color = "\001\033[0m\002";
	prompt.target = "$ ";
	if (prompt.pwd != NULL)
	{
		prompt.len = get_prompt_len(&prompt);
		prompt.prompt = ft_calloc(prompt.len, sizeof(char));
		if (prompt.prompt == NULL)
			return (NULL);
		build_prompt(&prompt);
	}
	free(prompt.pwd);
	return (prompt.prompt);
}
