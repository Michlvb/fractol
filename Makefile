# The $@ and $< are called automatic variables. The variable $@ represents the name of the target and $< represents the first prerequisite required to create the output file.

NAME = fractol.a

INCLUDE = -I./include

CC = gcc

RM = rm -f

SRC = main.c

OBJS = $(SRC:%.c=%.o)

MLX_DIR = ./mlx

MLX = $(MLX_DIR)/libmlx.dylib

MLXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(MLX)

	$(CC) $(OBJS) $(MLXFLAGS) $ -o $(NAME)

%.o: %.c
	$(CC) $(INCLUDE) -Wall -Wextra -Werror -Imlx -c $< -o $@ 

$(MLX): 
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX) .

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
