NAME = ft_printf.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = -I./includes

RM = rm -f

SRCS = srcs/ft_printf.c  srcs/ft_printchar.c srcs/ft_printhex.c \
			srcs/ft_printpointer.c srcs/ft_printstr.c srcs/ft_putnbr.c \
			srcs/ft_putunsigned.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

PHONY: clean, flcean, re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
