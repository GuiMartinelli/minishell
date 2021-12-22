# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 18:15:51 by proberto          #+#    #+#              #
#    Updated: 2021/12/22 10:02:46 by proberto         ###   ########.fr        #
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
	$(addprefix $(PATH_SRC)/builtins/, cd.c echo.c env.c export.c pwd.c unset.c) \
	$(addprefix $(PATH_SRC)/exec/, paths.c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -w
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
