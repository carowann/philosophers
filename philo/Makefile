# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 14:33:31 by cwannhed          #+#    #+#              #
#    Updated: 2025/08/05 17:01:29 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

VALGRIND =  valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all

INCLUDES = -I./includes

SRC =	src/main.c \
	src/parse.c \
	src/utils.c \
	src/thread_mgmt.c

FLAGS	= -g -pthread
FLAGS	+= -Wall -Werror -Wextra

$(NAME): $(SRC)
	@cc $(SRC) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t compilation completed$(RESET)"

all:$(NAME)

clean:
	@echo "$(RED)[$(NAME)]:\t clean$(RESET)"; \

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)]:\t fclean$(RESET)"; \

re: fclean all

.PHONY: all clean fclean re