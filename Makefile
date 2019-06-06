# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 20:56:30 by sofchami          #+#    #+#              #
#    Updated: 2019/05/28 15:28:35 by sofchami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CFLGS = -Wall -Werror -Wextra
SRC = lem_in.c
INC = libft/libft.a
Green = \033[0;32m
NC = \033[0m
CC = gcc
# SRCD = $(addprefix src/,$(SRC))
OBJ = $(subst .c,.o,$(SRC))

.PHONY: clean fclean re all

$(NAME): $(OBJ)
	@make re -C libft
	@gcc -c -O3 $(SRC)
	@gcc -o $(NAME) $(OBJ) $(INC)
	@echo "${Green}Compilation Succesfull${NC} "

all: $(NAME)

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "${Green}Cleaning succesfull${NC} "

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "${Green}FCleaning succesfull${NC} "

re: fclean all
