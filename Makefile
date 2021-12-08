# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 18:15:51 by proberto          #+#    #+#              #
#    Updated: 2021/12/08 07:18:50 by guferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = src
PATH_LIBFT = libs/libft

NAME = minishell
LIBFT = $(addprefix $(PATH_LIBFT)/, libft.a)
MAIN = $(PATH_SRC)/minishell.c
SRC = \
	$(addprefix $(PATH_SRC)/cli/, prompt.c cmd.c) \
	$(addprefix $(PATH_SRC)/builtins/, pwd.c cd.c echo.c env.c unset.c) \
	$(addprefix $(PATH_SRC)/parse_envv/, variables.c var_utils.c ft_split_value.c)
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
