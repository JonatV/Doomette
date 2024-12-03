NAME = doomette

INCPATH = includes/
MLX_PATH = $(INCPATH)minilibx_linux/
SRCS_PATH = sources/

INIT = $(SRCS_PATH)init/
HOOKS = $(SRCS_PATH)hooks/
COLORS = $(SRCS_PATH)colors/
MAP = $(SRCS_PATH)map/
RENDER = $(SRCS_PATH)render/
DRAWTOOLS = $(SRCS_PATH)draw_tools/
TOOLS = $(SRCS_PATH)tools/


INCLUDES = $(MLX_PATH)mlx.h \
			$(INCPATH)doomette.h

SRC = main.c \
		$(INIT)init_game_struct.c $(INIT)init_player_struct.c $(INIT)init_map_struct.c $(INIT)init_minimap_struct.c \
		$(HOOKS)close_game.c $(HOOKS)key_hooks.c $(HOOKS)mouse_hooks.c $(HOOKS)init_hooks.c $(HOOKS)player_hooks.c \
		$(COLORS)background.c \
		$(RENDER)render_all.c $(RENDER)draw_minimap.c $(RENDER)draw_rays.c $(RENDER)draw_vertex.c $(RENDER)optimization_helper.c \
		$(DRAWTOOLS)draw_rectangle.c $(DRAWTOOLS)draw_square.c \
		$(TOOLS)get_time.c

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
