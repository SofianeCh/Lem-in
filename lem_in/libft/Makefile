# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofchami <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 18:10:51 by sofchami          #+#    #+#              #
#    Updated: 2018/11/08 15:58:06 by sofchami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLGS = -Wall -Werror -Wextra
SRC = ft_isalpha.c ft_memccpy.c ft_memmove.c ft_strcmp.c ft_strlen.c\
	  ft_strrchr.c ft_atoi.c ft_isascii.c ft_memchr.c ft_memset.c ft_strcpy.c\
	  ft_strncat.c ft_strstr.c ft_bzero.c ft_isdigit.c ft_memcmp.c ft_strcat.c\
	  ft_strdup.c ft_strncmp.c ft_tolower.c ft_isalnum.c ft_isprint.c ft_memcpy.c\
	  ft_strchr.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_strncpy.c ft_putchar.c\
	  ft_putstr.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strclr.c ft_striteri.c\
	  ft_strmap.c ft_strdel.c ft_putchar_fd.c ft_strequ.c ft_strnequ.c ft_putnbr.c\
	  ft_striter.c ft_strmapi.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strrev.c\
	  ft_itoa.c ft_strsplit.c ft_putstr_fd.c ft_putnbr_fd.c ft_power.c ft_intlen.c\
	  ft_putendl.c ft_putendl_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c\
	  ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_word.c ft_lengtword.c\
	  ft_putnbr_base.c ft_itoa_base.c ft_list_size.c ft_abs.c ft_pos_i.c\
	  ft_ibu.c ft_printf.c ft_modifprintf.c ft_printing_oxp.c ft_printing_diusc.c\
	  ft_printint_float.c get_next_line.c
OBJ = $(subst .c,.o,$(SRC))
INC = libft.h

.PHONY: clean fclean re all

$(NAME):
	@gcc $(CFLGS) -c $(SRC) -I $(INC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
