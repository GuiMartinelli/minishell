/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 07:49:51 by guferrei          #+#    #+#             */
/*   Updated: 2022/02/17 19:35:18 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the size of a quoted argument
 * 
 * @param str pointer to first quotation marks
 * @param env link list of program environment variables
 * @param env_matrix matrix of Shell environment variables
 * @return int size of quoted string
 */
static int	get_quote_size(char *str, t_var *env, char **env_matrix)
{
	char	quote;
	int		size;
	int		aux;

	quote = *str;
	aux = 1;
	size = 0;
	while (str[aux] && str[aux] != quote)
	{
		if (str[aux] == '$' && quote != '\'')
		{
			size += (get_var_size(str, env, env_matrix) - 1);
			aux += mv_ptr('$', (str + aux));
		}
		size++;
		aux++;
	}
	return (size + 2);
}

/**
 * @brief Checks if a variable exists and if it is expandable
 * 
 * @param str pointer to variable name
 * @param env link list of program environment variables
 * @param env_matrix matrix of Shell environment variables
 * @return int size of variable value
 */
static int	check_var(char *str, t_var *env, char **env_matrix)
{
	int		size;
	char	*err;

	if (*str == '~')
		size = get_var_size("~", env, env_matrix);
	if (*str == '?')
	{
		err = ft_itoa(g_error_status);
		size = ft_strlen(err);
		free_n_null(err);
	}
	else
		size = get_var_size(str, env, env_matrix);
	return (size);
}

/**
 * @brief Get the string size after parsed and variables expanded.
 * 
 * @param str original string
 * @param env link list of program environment variables
 * @param env_matrix matrix of Shell environment variables
 * @return int size of parsed string
 */
static int	get_string_size(char *str, t_var *env, char **env_matrix)
{
	int		size;
	int		aux;

	size = 0;
	aux = 0;
	while (str[aux])
	{
		if ((str[aux] == '\'' || str[aux] == '"')
			&& is_quotes((str + aux), str[aux]))
		{
			size += get_quote_size((str + aux), env, env_matrix);
			aux += (mv_ptr(str[aux], (str + aux)) - 1);
		}
		else if (str[aux] == ' ' && str[aux + 1] == ' ')
			aux += (mv_ptr(' ', (str + aux)) - 1);
		else if (is_variable((str + aux), 0))
		{
			size += (check_var((str + aux), env, env_matrix));
			aux += (mv_ptr('$', (str + aux)) - 1);
		}
		else
			size++;
		aux++;
	}
	return (size + 1);
}

/**
 * @brief Expand variables when necessary and handle spaces in a row.
 * 
 * @param parse struct containing data of original and parsed string
 * @param env linked list of program environment variables
 * @param env_matrix matrix of Shell environment variables
 */
static void	ft_lexer_sub(t_parse *parse, t_var *env, char **env_matrix)
{
	while (parse->str[parse->idx1])
	{
		if ((parse->str[parse->idx1] == '\'' || parse->str[parse->idx1] == '"')
			&& is_quotes((parse->str + parse->idx1), parse->str[parse->idx1])
			&& !parse->quotes)
			parse->quotes = parse->str[parse->idx1];
		else if (parse->str[parse->idx1] == parse->quotes)
			parse->quotes = 0;
		if (parse->str[parse->idx1] == ' '
			&& parse->str[parse->idx1 + 1] == ' ' && !parse->quotes)
			parse->idx1 += mv_ptr(' ', (parse->str + parse->idx1));
		else if (is_variable((parse->str + parse->idx1), parse->quotes))
		{
			parse->idx2 += var_value_cpy((parse->parsed + parse->idx2),
					(parse->str + parse->idx1), env, env_matrix);
			parse->idx1 += mv_ptr(parse->str[parse->idx1],
					(parse->str + parse->idx1));
		}
		else
			parse->parsed[parse->idx2++] = parse->str[parse->idx1++];
	}
}

/**
 * @brief Get a string and format to a matrix which the programs interprets
 * 
 * @param str string to format
 * @param env linked list of program environment variables
 * @param envp matrix of shell environment variables
 * @return char** matrix parsed and formated
 */
char	**ft_lexer(char *str, t_var *env, char **envp)
{
	t_parse	parse;
	char	**splitted;

	parse.idx1 = 0;
	parse.idx2 = 0;
	parse.str = str;
	parse.quotes = 0;
	parse.parsed = ft_calloc((get_string_size(str, env, envp) + 1),
			sizeof(char));
	if (!parse.parsed)
		return (NULL);
	ft_lexer_sub(&parse, env, envp);
	parse.parsed = parse_spaces(parse.parsed);
	splitted = ft_split_string(parse.parsed);
	free_n_null(parse.parsed);
	return (splitted);
}
