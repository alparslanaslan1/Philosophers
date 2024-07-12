# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 12:33:35 by alaslan           #+#    #+#              #
#    Updated: 2024/07/09 18:04:14 by alaslan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC = gcc
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -pthread -g

RM = rm -rf

SRC = main.c \
		init_table.c \
		utils.c \
		threads_start.c \
		cleanup.c \
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
