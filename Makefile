# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 12:33:35 by alaslan           #+#    #+#              #
#    Updated: 2024/09/12 18:12:34 by alaslan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC = gcc
CFLAGS	= -Wall -Wextra -Werror

RM = rm -rf

SRC = main.c			\
		created_table.c	\
		utils.c			\
		threads_start.c	\
		cleanup.c		\
		simulation.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(SRC)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
re: fclean all

r: re
f: fclean
c: clean

.phony: all clean fclean re
