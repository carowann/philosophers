# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 14:33:31 by cwannhed          #+#    #+#              #
#    Updated: 2025/11/03 11:41:17 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

INCLUDES = -I./includes

SRC =	src/main.c		\
	src/parse.c		\
	src/utils.c		\
	src/thread_mgmt.c	\
	src/routine.c		\
	src/cleanup.c		\
	src/thread_safety.c	\
	src/monitor_routine.c

FLAGS	= -g -pthread
FLAGS	+= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	@cc $(SRC) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t compilation completed$(RESET)"

clean:
	@echo "$(RED)[$(NAME)]:\t clean$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)]:\t fclean$(RESET)"

re: fclean all

.PHONY: all clean fclean re