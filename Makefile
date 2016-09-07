# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/06 15:15:02 by jcamhi            #+#    #+#              #
#    Updated: 2016/09/07 18:33:51 by jcamhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = malloc.c \
						utils.c \
						page.c \
						tiny.c \
						small.c \
						large.c

OBJ_PATH = ./obj/
INC_PATH = ./includes

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SYM_NAME = libft_malloc.so

NAME_TEST = t_malloc
NAME_TEST_OBJ = $(OBJ_PATH)t_malloc.o

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -lft

LIB_DIR=./lib

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME) $(SYM_NAME) $(NAME_TEST)

$(NAME) : $(OBJ)
	@mkdir -p $(LIB_DIR)
	make -C libsrcs/libft
	$(CC) $(CFLAGS) $^ -L $(LIB_DIR) $(LFLAGS) -shared -o $@
	rm -fv $(NAME_TEST_OBJ)

$(SYM_NAME) :
	ln -s $(NAME) ./$(SYM_NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -fv $(NAME_TEST_OBJ)
	rmdir -p $(OBJ_PATH) 2> /dev/null || true
	make -C libsrcs/libft clean

fclean: clean
	rm -fv $(NAME)
	rm -fv $(SYM_NAME)
	make -C libsrcs/libft fclean
	@rmdir lib 2> /dev/null || true
	rm -f $(NAME_TEST)

re: fclean all

$(NAME_TEST_OBJ): main.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME_TEST): $(NAME_TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -L $(LIB_DIR) $(SYM_NAME) -o $@

leaks: all
	 valgrind --leak-check=full ./$(NAME_TEST)

leaks-le-pen: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME_TEST)

.PHONY : all clean fclean re
