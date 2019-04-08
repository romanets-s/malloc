# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/24 21:10:39 by dverbyts          #+#    #+#              #
#    Updated: 2018/11/24 21:10:47 by dverbyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fPIC

SRC = ft_malloc.c \
	  ft_malloc2.c \
	  ft_free.c \
	  ft_realloc.c \
	  show_alloc_mem.c \
	  ft_bzero.c \
	  ft_memcpy.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME):  $(OBJ)
	@$(CC) -shared -o $(NAME) $(OBJ) $(LIB)
	@ln -s $(NAME) libft_malloc.so
	@echo "!"
	@echo "$(NAME) compiled\033[0m"

%.o : %.c
	@$(CC) -c $(CFLAGS) $<
	@printf "\033[32m."

clean :
	@/bin/rm -f $(OBJ) 
	@echo "\033[31m$(NAME) objects deleted\033[0m"

fclean : clean
	@/bin/rm -f $(NAME) libft_malloc.so
	@echo "\033[31m$(NAME) deleted\033[0m"

re : fclean all
