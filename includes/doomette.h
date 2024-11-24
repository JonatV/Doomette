# ifndef DOOMETTE_H
#define DOOMETTE_H

# include "minilibx_linux/mlx.h"
# include "X11/Xutil.h" // use for MotionNotify and PointerMotionMask
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#define TITLE "doomette"
#define WIN1_SX 1200
#define WIN1_SY 600

#define MAP_W 24
#define MAP_H 24

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void	*mlx;	// will be a xvar struct
	void	*win1;	// will be a t_win_list struct
	void	*img1;	// will be a t_img struct
	t_img	bg;
	int		xpm1_x;
	int		xpm1_y;
	int		**map;
}				t_game;

/*----------------  init_map.c  ---------------*/
int		draw_map(t_game *game);

/*----------------  init_map.c  ---------------*/
int		init_map(t_game *game);

/*----------------  background.c  ---------------*/
int		fill_background(t_game *game);

/*----------------  key_hooks.c  ---------------*/
int		key_win1(int key, void *p);

/*----------------  close_game.c  ---------------*/
int		close_game(void *p);

/*----------------  init_hooks.c  ---------------*/
void	init_hooks(t_game *game);

/*----------------  mouse_hooks.c  ---------------*/
int		mouse_move_win1(int x, int y, void *p);
int		mouse_btn_win1(int key, void *p);

# endif
