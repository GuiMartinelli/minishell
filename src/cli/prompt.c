/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by proberto          #+#    #+#             */
/*   Updated: 2022/02/07 06:39:38 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Concatenate strings that make up the prompt.
 * 
 * @param user prompt user struct
 * @param pwd prompt pwd struct
 * @param target prompt target struct
 * @param len total length of the sum of all strings in the structures
 * @return prompt string
 */
static char	*build(t_prompt *user, t_prompt *pwd, t_prompt *target, size_t len)
{
	char	*prompt;

	prompt = ft_calloc(len + 1, sizeof(char));
	ft_strlcat(prompt, user->prefix_color, len);
	ft_strlcat(prompt, user->label, len);
	ft_strlcat(prompt, user->suffix_color, len);
	ft_strlcat(prompt, " in ", len);
	ft_strlcat(prompt, pwd->prefix_color, len);
	ft_strlcat(prompt, pwd->label, len);
	ft_strlcat(prompt, pwd->suffix_color, len);
	ft_strlcat(prompt, target->prefix_color, len);
	ft_strlcat(prompt, target->label, len);
	ft_strlcat(prompt, target->suffix_color, len);
	return (prompt);
}

/**
 * @brief Initialize the prompt target struct.
 * 
 * @param target struct to be initialized
 * @return void
 */
static void	init_target_prompt(t_prompt *target)
{
	target->label = "❯ ";
	if (g_error_status > 0)
		target->prefix_color = RED;
	else
		target->prefix_color = GREEN;
	target->suffix_color = RESET;
	target->len = ft_strlen(target->label)
		+ ft_strlen(target->prefix_color)
		+ ft_strlen(target->suffix_color);
}

/**
 * @brief Initialize the prompt pwd struct.
 * 
 * @param pwd struct to be initialized
 * @param user user structure
 * @return void
 */
static void	init_pwd_prompt(t_prompt *pwd, t_prompt *user)
{
	char	*aux;
	char	*pwd_aux;

	pwd->label = get_pwd();
	pwd->prefix_color = BLUE;
	pwd->suffix_color = RESET;
	pwd->len = ft_strlen(pwd->label)
		+ ft_strlen(pwd->prefix_color)
		+ ft_strlen(pwd->suffix_color);
	aux = ft_strnstr(pwd->label, user->label, ft_strlen(pwd->label));
	if (aux)
	{
		if (ft_strlen(aux) == ft_strlen(user->label))
			aux = aux + ft_strlen(user->label) - 1;
		else
			aux = aux + ft_strlen(user->label);
		pwd_aux = ft_calloc(ft_strlen(aux) + ft_strlen("~") + 2, sizeof(char));
		ft_strlcat(pwd_aux, "~", ft_strlen(aux) + ft_strlen("~"));
		ft_strlcat(pwd_aux, aux, ft_strlen(aux) + ft_strlen("~"));
		free(pwd->label);
		pwd->label = pwd_aux;
	}
}

/**
 * @brief Initialize the prompt user struct.
 * 
 * @param user struct to be initialized
 * @param env structure containing the environment variables
 * @return void
 */
static void	init_user_prompt(t_prompt *user, t_env_var *env)
{
	user->label = hash_table("USER", env->list);
	user->prefix_color = YELLOW;
	user->suffix_color = RESET;
	user->len = ft_strlen(user->label)
		+ ft_strlen(user->prefix_color)
		+ ft_strlen(user->suffix_color);
}

/**
 * @brief Create the prompt string to be displayed in the cli 
 * (acronym for command line).
 * 
 * @param env structure containing the environment variables
 * @return the char* pointer to a new prompt
 */
char	*new_prompt(t_env_var *env)
{
	t_prompt	user;
	t_prompt	pwd;
	t_prompt	target;
	char		*prompt;
	size_t		len;

	init_user_prompt(&user, env);
	init_pwd_prompt(&pwd, &user);
	init_target_prompt(&target);
	len = user.len + pwd.len + target.len + ft_strlen(" in ");
	prompt = build(&user, &pwd, &target, len);
	free(user.label);
	free(pwd.label);
	return (prompt);
}
