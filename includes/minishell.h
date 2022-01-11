/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:14 by proberto          #+#    #+#             */
/*   Updated: 2022/01/11 16:00:34 by proberto         ###   ########.fr       */
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

typedef struct s_parse
{
	char	*parsed;
	char	*str;
	int		idx1;
	int		idx2;
	char	quotes;
}				t_parse;

/**
 * Command line interface (cli)
 */
char	*new_prompt(void);
void	eval(char *command_line, t_var *env_list, char **envp);

/**
 * System
 */
void	sig_handler(int sign);
t_var	*env_variables(char **env);
int		new_variable(t_var **env_list, char *name, char *value);
int		update_var(t_var *env_list, char *name, char *value);
char	**ft_split_value(char const *s, char c);
char	*get_var_value(char *name, t_var *var_list);
void	free_var_list(t_var *var_list);
void	free_n_null(void *ptr);
void	free_var(t_var *var);

/**
 * Builtins
 */
char	*get_pwd(void);
void	pwd(int fd);
void	export(t_var *env_list, char **var);
void	env(t_var *list, int fd);
void	echo(char **str, int fd);
t_var	*unset(t_var *var_list, char **var_name);
void	cd(char *dir, t_var *env_list);
void	ft_exit(void);

/**
 * Execve
 * 
 */
char	**parse_paths(char **env);
char	*build_path(char *env_path, char *cmd);
char	*check_path(char **env_path, char *cmd);

/**
 * Parse
 * 
 */
int		is_quotes(char *str, char q);
int		mv_ptr(char mode, char *str);
int		get_var_size(char *str, t_var *env, t_var *local);
int		var_value_cpy(char *dest, char *src, t_var *env, t_var *local);
char	*string_parse(char *str, t_var *env, t_var *local);
char	**ft_split_string(char *s);

#endif
