# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 18:15:51 by proberto          #+#    #+#              #
#    Updated: 2022/01/17 21:11:13 by guferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = src
PATH_LIBFT = libs/libft

NAME = minishell
LIBFT = $(addprefix $(PATH_LIBFT)/, libft.a)
MAIN = $(PATH_SRC)/minishell.c
SRC = \
	$(addprefix $(PATH_SRC)/cli/, prompt.c cmd.c) \
	$(addprefix $(PATH_SRC)/system/, env_var.c utils_var.c free_var.c signals.c) \
	$(addprefix $(PATH_SRC)/builtins/, cd.c echo.c env.c export.c pwd.c unset.c ft_exit.c) \
	$(addprefix $(PATH_SRC)/exec/, paths.c) \
	$(addprefix $(PATH_SRC)/parse/, parse_utils.c parse_var_utils.c string_parse.c ft_split_string.c) \
	$(addprefix $(PATH_SRC)/redirection/, out_redirect.c) \
	$(addprefix $(PATH_SRC)/pipes/, run_cmds.c)
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
