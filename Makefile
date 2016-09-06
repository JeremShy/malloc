# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/06 15:15:02 by jcamhi            #+#    #+#              #
#    Updated: 2016/09/06 15:23:17 by jcamhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c

OBJ_PATH = ./obj/
INC_PATH = ./includes

NAME = test_malloc
NAMELIB = lib$(NAME).a

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -ltermcap

LIB_DIR=./lib
STATIC_LIBS= $(LIB_DIR)/libft.a

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(NAME) : $(OBJ)
	@mkdir -p $(LIB_DIR)
	make -C libsrcs/libft
	@ar -cr $(NAMELIB) $^
	@ranlib $(NAMELIB)
	$(CC) $(CFLAGS) $(NAMELIB) $(STATIC_LIBS) $(LFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rmdir -p $(OBJ_PATH) 2> /dev/null || true
	make -C libsrcs/libft clean

fclean: clean
	rm -fv $(NAME) $(NAMELIB)
	make -C libsrcs/libft fclean
	@rmdir lib 2> /dev/null || true

re: fclean all

leaks: all
	 valgrind --leak-check=full ./$NAME

.PHONY : all clean fclean re
