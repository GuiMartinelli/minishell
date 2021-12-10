/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:14 by proberto          #+#    #+#             */
/*   Updated: 2021/12/10 08:37:30 by guferrei         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*name;
	char	*option;
	char	*arg;
}			t_cmd;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

/**
 * Command line interface (cli)
 */
char	*new_prompt(void);
void	eval(char *command_line, t_var *env_list);

/**
 * System
 */
char	**ft_split_value(char const *s, char c);
void	free_n_null(void *ptr);
void	free_var(t_var *var);
t_var	*env_variables(char **env);
char	*get_var_value(char *name, t_var *var_list);

/**
 * Builtins
 */
char	*get_pwd(void);
void	pwd(int fd);
int		export(t_var **env, t_var *var);
void	env(t_var *list, int fd);
void	echo(char *op, char *str);
t_var	*unset(t_var *var_list, char *var_name);
void	cd(char *dir);
void	b_exit(void);

#endif
