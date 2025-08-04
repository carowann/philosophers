# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 14:33:31 by cwannhed          #+#    #+#              #
#    Updated: 2025/08/04 15:55:42 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

VALGRIND =  valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all

INCLUDES = -I./includes

SRC = src/main.c \

FLAGS	= -g --pthread
FLAGS	+= -Wall -Werror -Wextra

$(NAME): $(SRC)
	@cc $(SRC) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t comilation completed$(RESET)"

all:$(NAME)

clean:
	@echo "$(RED)[$(NAME)]:\t CLEAN$(RESET)"; \

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)]:\t FCLEAN$(RESET)"; \

re: fclean all

.PHONY: all clean fclean re