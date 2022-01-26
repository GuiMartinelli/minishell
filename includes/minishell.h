/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartinelli <gmartinelli@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:10:14 by proberto          #+#    #+#             */
/*   Updated: 2022/01/26 08:19:07 by gmartinelli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define STDIN_FILENO 0
# define STDOUT_FILENO 1

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
	char	**option;
	char	**env;
}			t_cmd;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct s_parse
{
	char	*parsed;
	char	*str;
	int		idx1;
	int		idx2;
	char	quotes;
}			t_parse;

/**
 * Command line interface (cli)
 */
char	*new_prompt(void);
void	eval(char *command_line, t_var *env_list, char **envp);

/**
 * System
 */
void	redisplay_prompt(int signal);
void	interrupt_process(int signal);
void	quit_process(int signal);
t_var	*env_variables(char **env);
int		new_variable(t_var **env_list, char *name, char *value);
int		update_var(t_var *env_list, char *name, char *value);
char	**ft_split_value(char const *s, char c);
char	*get_var_value(char *name, t_var *var_list);
void	free_var_list(t_var *var_list);
void	free_n_null(void *ptr);
void	free_var(t_var *var);
void	free_matrix(char **matrix);

/**
 * Launch
 */
int		launch_builtins(char *cmd, char **arg, t_var *env_list, int fd);
void	launch_execve(char *path, char **arg, char **envp, int fd[2]);
void	run_cmds(char **matrix, char **envp, int input, int output, t_var *env_list);

/**
 * Builtins
 */
char	*get_pwd(void);
void	pwd(int fd);
void	export(t_var *env_list, char **var);
void	env(t_var *list, int fd);
void	echo(char **str, int fd);
t_var	*unset(t_var *env_list, char **var_name);
void	cd(char *dir, t_var *env_list);
void	ft_exit(void);

/**
 * Execve
 * 
 */
char	**parse_paths(t_var *env_list);
char	*build_path(char *env_path, char *cmd);
char	**parse_cmd(t_cmd *cmd, char **matrix, char **env, t_var *env_list);
char	*check_path(char **env_path, char *cmd);

/**
 * Parse
 * 
 */
int		is_quotes(char *str, char q);
int		is_variable(char *c);
int		mv_ptr(char mode, char *str);
int		get_var_size(char *str, t_var *env);
int		var_value_cpy(char *dest, char *src, t_var *env);
char	*parse_spaces(char *str);
char	**string_parse(char *str, t_var *env);
char	**ft_split_string(char *s);

/**
 * Redirects
 * 
 */
int		check_redirects(char **matrix, char c);
char	*file_name(char **matrix, char c);
int		output_redirects(char **matrix);
int		input_redirects(char **matrix);
int		heredocs_prompt(char **matrix, char *delimiter);

#endif
