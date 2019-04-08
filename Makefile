
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif



NAME = libft_malloc_$(HOSTTYPE).so
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = malloc.c
OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) -shared $(OBJECTS) -o $(NAME)
	@ln -s $(NAME) libft_malloc.so

%.o: %.c
	@gcc $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft_malloc.so

re: fclean all
