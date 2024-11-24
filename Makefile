NAME = doomette

INCPATH = includes/
MLX_PATH = $(INCPATH)minilibx_linux/
SRCS_PATH = sources/

HOOKS = $(SRCS_PATH)hooks/
COLORS = $(SRCS_PATH)colors/
MAP = $(SRCS_PATH)map/

INCLUDES = $(MLX_PATH)mlx.h \
			$(INCPATH)doomette.h

SRC = main.c \
		$(HOOKS)close_game.c $(HOOKS)key_hooks.c $(HOOKS)mouse_hooks.c $(HOOKS)init_hooks.c \
		$(COLORS)background.c \
		$(MAP)init_map.c $(MAP)draw_map.c

OBJ = $(SRC:.c=.o)

CC = clang
INCS = -I$(INCPATH)
LIBS = includes/minilibx_linux/libmlx_Linux.a \
		-Lincludes/minilibx_linux -lmlx -lXext -lX11 -lm

# Separate flags for compilation and linking
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g $(INCS)
LDFLAGS = -fsanitize=address -g $(LIBS)
# CFLAGS = -Wall -Wextra -Werror $(INCS)
# LDFLAGS = $(LIBS)

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	./$(NAME)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
