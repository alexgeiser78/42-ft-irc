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

BLUE     	= \033[0;34m
GREEN    	= \033[0;32m
RED      	= \033[0;31m
YELLOW   	= \033[0;33m
NO_COLOR    = \033[m

SRCS = 	$(wildcard ./src/Command/*.cpp) \
		$(wildcard ./src/Network/*.cpp) \
		./src/main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

NAME = ircserv

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

HEADER = -I ./includes

RM = rm -f

%.o: %.cpp
	@$(CC) $(FLAGS) $(HEADER) -c $< -o $@
	@echo "$(YELLOW)Compiled $< to $@$(NO_COLOR)"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(HEADER) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) generated$(NO_COLOR)"

clean:
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(BLUE)Objects files removed$(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable $(NAME) removed$(NO_COLOR)"

re: fclean all

leaks:
	valgrind --leak-check=full ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re leaks
