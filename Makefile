# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 17:26:08 by cfriot            #+#    #+#              #
#    Updated: 2015/04/21 18:21:07 by cfriot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = ft_cd_tools.c \
	  ft_check.c  \
	  ft_check_access.c  \
	  ft_do_cd.c  \
	  ft_do_cd2.c      \
	  ft_env_tools.c   \
	  ft_get_env.c  \
	  ft_parseur.c       \
	  ft_setenv.c        \
	  ft_sh1.c          \
	  ft_sighandler.c   \
	  ft_tools.c        \
	  ft_x_param_setenv.c \
	  get_next_line.c     \
	  ft_check_env.c

OBJ = $(SRC:.c=.o)

.PHONY: all libft clean fclean re

all : libft $(NAME)

$(NAME):  $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a 
	@echo "!"
	@echo "$(NAME) compiled\033[0m"

libft :
	@make -C libft/

%.o : %.c
	@$(CC) -c $(CFLAGS) -I./includes/ -I./libft/includes $<
	@printf "\033[32m."

clean :
	@make -C libft/ clean
	@/bin/rm -f $(OBJ)
	@echo "\033[31mminishell1 objects deleted\033[0m"

fclean : allclean
	@/bin/rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\033[0m"

allclean :
	@make -C libft/ fclean
	@/bin/rm -f $(OBJ)
	@echo "\033[31mminishell1 objects deleted\033[0m"

re : fclean all
