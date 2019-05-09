# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malavent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 11:25:29 by malavent          #+#    #+#              #
#    Updated: 2019/05/09 08:46:23 by malavent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
HEADERS = -I Includes
SRCS_NAME = other_tools.c parsing.c set_fonction.c main.c pixel.c fill_img.c\
			read_map.c tools.c handle_keys.c segment.c
SRCS = $(addprefix srcs/, $(SRCS_NAME))
OBJS = $(SRCS_NAME:.c=.o)
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = libft/libft.a
LXFLAGS = -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): lib
	@echo "FDF Compiling:	\033[1;32mDONE\033[m"
	@$(CC) -c $(CFLAGS) $(HEADERS) $(SRCS)
	@$(CC) -o $(NAME) $(LFLAGS) $(LXFLAGS) $(OBJS)
	@echo "Compilation over: \033[1;32mDONE\033[m"

lib:
	make -C libft 

clean:
	@rm -f $(OBJS)
	@echo "Fdf Clean Objects"
fclean: clean
	@rm -f $(NAME)
	@echo "Fdf Clean Objects + bin"

re: fclean all

.PHONY: all clean fclean re
