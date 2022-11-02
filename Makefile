NAME = fractol.a

INCLUDE = -I./include

CC = gcc -Wall -Werror -Wextra

RM = rm -f

SRC = fractol.c \
				colors.c \
				errors.c \
				utils.c \
				events.c \
				draw_fractal.c \
				extra_utils.c

OBJS = $(SRC:%.c=%.o)

SPECIAL_RM = libmlx.dylib

FT_PRINTF_DIR = ./ft_printf

FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a

MLX_DIR = ./mlx

MLX = $(MLX_DIR)/libmlx.dylib

MLXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(FT_PRINTF)

	$(CC) $(OBJS) $(FT_PRINTF) $(MLXFLAGS) -g -o $(NAME)

%.o: %.c
	$(CC) -g -c $(INCLUDE) -Imlx -c $< -o $@ 

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX): 
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX) .

PHONY: clean, re, fclean

clean:
	$(MAKE) fclean -C $(FT_PRINTF_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJS)
	$(RM) $(SPECIAL_RM)

fclean: clean
	$(RM) $(NAME)

re: fclean all
