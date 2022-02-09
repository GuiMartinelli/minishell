# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 18:15:51 by proberto          #+#    #+#              #
#    Updated: 2022/02/09 17:57:47 by proberto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = src
PATH_LIBFT = libs/libft

NAME = minishell
LIBFT = $(addprefix $(PATH_LIBFT)/, libft.a)
MAIN = $(PATH_SRC)/minishell.c
SRC = \
	$(addprefix $(PATH_SRC)/system/, signals.c env_var.c utils_var.c utils.c) \
	$(addprefix $(PATH_SRC)/cli/, repl.c prompt.c) \
	$(addprefix $(PATH_SRC)/parse/, ft_lexer_utils.c ft_lexer.c ft_tokenizer.c) \
	$(addprefix $(PATH_SRC)/parse/, parse_var_utils.c parse_spaces.c) \
	$(addprefix $(PATH_SRC)/parse/, parse_space_utils.c parse_cmds.c) \
	$(addprefix $(PATH_SRC)/redirections/, input.c here_docs.c output.c utils.c) \
	$(addprefix $(PATH_SRC)/eval/, eval.c run_cl.c run_cl_utils.c utils.c paths.c) \
	$(addprefix $(PATH_SRC)/builtins/, cd.c echo.c env.c export.c pwd.c unset.c ft_exit.c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

all: $(NAME)

$(NAME):	$(LIBFT)
	$(CC) $(CFLAGS) $(MAIN) $(SRC) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

clean:
	@$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	@$(MAKE) fclean -C $(PATH_LIBFT)
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
