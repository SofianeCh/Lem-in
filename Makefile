# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 20:56:30 by sofchami          #+#    #+#              #
#    Updated: 2019/06/14 13:00:45 by sofchami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CFLGS = -Wall -Werror -Wextra
SRC = lem_in.c parse.c crea_map.c parse2.c bfs.c crea_path.c merge.c solve.c\
	error_control.c
INC = libft/libft.a
Green = \033[0;32m
NC = \033[0m
CC = gcc
SRCD = $(addprefix src/,$(SRC))
OBJ = $(subst .c,.o,$(SRCD))

.PHONY: clean fclean re all

$(NAME): $(OBJ)
	@make re -C libft
	@gcc -c -O3 $(SRCD) $(CGLGS)
	@gcc -o $(NAME) $(OBJ) $(INC) -g -fsanitize=address
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
