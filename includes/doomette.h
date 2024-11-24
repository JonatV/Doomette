# ifndef DOOMETTE_H
#define DOOMETTE_H

# include "minilibx_linux/mlx.h"
# include "X11/Xutil.h" // use for MotionNotify and PointerMotionMask
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define PI 3.1415926535

#define TITLE "doomette"
#define WIN1_SX 1200
#define WIN1_SY 600

#define MAP_W 12
#define MAP_H 12

#define MAP_TILE 50

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define PLAYER_SIZE 11
#define PLAYER_SPEED 10

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	float		x;
	float		y;
	float	pa;  // player angle
	float	pdx; // player delta x
	float	pdy; // player delta y
	int		size; //todo - will have to be zoomed also
	int		dir;
}	t_player;

typedef struct s_game
{
	void	*mlx;	// will be a xvar struct
	void	*win1;	// will be a t_win_list struct
	void	*img1;	// will be a t_img struct
	t_img	bg;
	t_img	shape1;
	t_img	mini_map;
	int		zoom;
	int		xpm1_x;
	int		xpm1_y;
	int		**map;
	t_player	player;
}				t_game;

/*----------------  player_hooks.c  ---------------*/
int		move_player(t_game *game, int key);

/*----------------  init_map.c  ---------------*/
int		draw_map(t_game *game);

/*----------------  init_map.c  ---------------*/
int		init_map(t_game *game);

/*----------------  background.c  ---------------*/
int		fill_background(t_game *game);
int		rectangle(t_game *game, int w, int h, int x, int y);

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
