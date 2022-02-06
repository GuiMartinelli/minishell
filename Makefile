# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 18:15:51 by proberto          #+#    #+#              #
#    Updated: 2022/02/06 08:29:19 by proberto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = src
PATH_LIBFT = libs/libft

NAME = minishell
LIBFT = $(addprefix $(PATH_LIBFT)/, libft.a)
MAIN = $(PATH_SRC)/minishell.c
SRC = \
	$(addprefix $(PATH_SRC)/cli/, prompt.c cmd.c utils.c cmd_utils.c) \
	$(addprefix $(PATH_SRC)/system/, env_var.c utils_var.c free_var.c signals.c) \
	$(addprefix $(PATH_SRC)/builtins/, cd.c echo.c env.c export.c pwd.c unset.c ft_exit.c) \
	$(addprefix $(PATH_SRC)/exec/, paths.c) \
	$(addprefix $(PATH_SRC)/parse/, parse_utils.c parse_var_utils.c string_parse.c ft_split_string.c parse_spaces.c parse_space_utils.c) \
	$(addprefix $(PATH_SRC)/redirections/, input.c here_docs.c output.c utils.c) \
	$(addprefix $(PATH_SRC)/pipes/, parse_cmds.c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

all: $(NAME)

$(NAME):	$(LIBFT)
	$(CC) $(CFLAGS) $(MAIN) $(SRC) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

clean:
	rm $(NAME)
#	@$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
#	@$(MAKE) fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean re
