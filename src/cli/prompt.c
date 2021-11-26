/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by proberto          #+#    #+#             */
/*   Updated: 2021/11/22 11:43:57 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_prompt_len(t_prompt *prompt)
{
	return (ft_strlen(prompt->pwd)
		+ ft_strlen(prompt->prefix_color)
		+ ft_strlen(prompt->suffix_color)
		+ ft_strlen(prompt->target)
		+ 1);
}

static void	build_prompt(t_prompt *prompt)
{
	ft_strlcat(prompt->prompt, prompt->prefix_color, prompt->len);
	ft_strlcat(prompt->prompt, prompt->pwd, prompt->len);
	ft_strlcat(prompt->prompt, prompt->suffix_color, prompt->len);
	ft_strlcat(prompt->prompt, prompt->target, prompt->len);
}

char	*new_prompt(void)
{
	t_prompt	prompt;

	prompt.pwd = get_pwd();
	prompt.prefix_color = "\033[31;33m";
	prompt.suffix_color = "\033[0m";
	prompt.target = "$ ";
	if (prompt.pwd != NULL)
	{
		prompt.len = get_prompt_len(&prompt);
		prompt.prompt = malloc(prompt.len * sizeof(char));
		if (prompt.prompt == NULL)
			return (NULL);
		build_prompt(&prompt);
	}
	free(prompt.pwd);
	return (prompt.prompt);
}
