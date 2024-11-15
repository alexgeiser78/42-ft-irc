# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ageiser <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 12:48:51 by ageiser           #+#    #+#              #
#    Updated: 2024/11/15 12:48:53 by ageiser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard ./src/command/*.c) \
		$(wildcard ./src/network/*.c)

OBJS = $(SRCS:.c=.o)

NAME = ircserv

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

HEADER = -I ./includes

RM = rm -f

$(OBJS): %.o: %.c
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@
	@echo "Compiled $< to $@"

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(HEADER) $(OBJS) -o $(NAME)
	@echo "Executable $(NAME) generated"

clean:
	$(RM) $(OBJS)
	@echo "Objects files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "Executable $(NAME) removed"

re: fclean all

leaks:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re leaks
