# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 21:36:12 by jlucas-s          #+#    #+#              #
#    Updated: 2023/05/24 21:36:14 by jlucas-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philo
ARGS =			4 401 200 200

CC =			cc

FLAGS =			-Wall -Wextra -Werror

INC =			-I ./include

GREEN =			\033[1;32m 
YELLOW =		\033[1;33m 
RED =			\033[1;31m 
NOCOLOR =		\033[0m

SRCS =			src/main.c		\
				src/init.c		\
				src/utils.c		\
				src/threads.c	\
				src/routines.c	\

OBJS_DIR = 		./objects
OBJS =			${SRCS:%.c=$(OBJS_DIR)/%.o}

all: ${NAME}

${NAME}: ${OBJS}
	@ echo "${YELLOW}-=- Compiling... -=-${NOCOLOR}"
	@ $(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread
	@ echo "${GREEN}-=- PHILOSOPHERS MANDATORY SUCCESSFUL COMPILED -=-${NOCOLOR}"
	
$(OBJS_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(INC) $(FLAGS) -c $< -o $@

clean:
	@ rm -rf $(OBJS_DIR)
	@ echo "${RED}-=- CLEANED -=-${NOCOLOR}"

fclean: clean
	@ rm -f $(NAME)

re: fclean all

run: ${NAME}
	@./$(NAME) ${ARGS}

valgrind: ${NAME}
	valgrind --leak-check=full  --show-leak-kinds=all --track-origins=yes ./$(NAME) ${ARGS}

.PHONY: all clean fclean run valgrind
