NAME = doomette

INCPATH = includes/
MLX_PATH = $(INCPATH)minilibx_linux/

INCLUDES = $(MLX_PATH)mlx.h \
			$(INCPATH)doomette.h

SRC = main.c
OBJ = $(SRC:.c=.o)

CC = clang
INCS = -I$(INCPATH)
LIBS = includes/minilibx_linux/libmlx_Linux.a \
		-Lincludes/minilibx_linux -lmlx -lXext -lX11 -lm

# Separate flags for compilation and linking
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g $(INCS)
LDFLAGS = -fsanitize=address -g $(LIBS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
