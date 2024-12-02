# ifndef DOOMETTE_H
#define DOOMETTE_H

# include "minilibx_linux/mlx.h"
# include "X11/Xutil.h" // use for MotionNotify and PointerMotionMask
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>

# define DR 0.0174533
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2

#define TITLE "doomette"
#define WIN1_SX 1200
#define WIN1_SY 600

#define MAP_W 12
#define MAP_H 12

#define MAP_TILE 30
#define MAP_LOW_TILE 30
#define MAP_BIG_TILE 50

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define PLAYER_SIZE 1
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

typedef struct s_mini_map
{
	t_img	img;
	float	width;
	float	height;
	int		tile; // size of one tile
	bool	map_focus; // to know wether the map is in big or not
	bool	is_square; // to know if the map is a square or circle
}	t_mini_map;

typedef struct s_xpm
{
	void	*img;
	int		x;
	int		y;
}	t_xpm;

typedef struct s_game
{
	void		*mlx;	// will be a xvar struct
	void		*win1;	// will be a t_win_list struct

	// GRAPHICS
	t_xpm		mossy_brick;
	t_img		bg;
	t_img		shape1;

	// MAP
	int			**map;

	// MINI MAP
	bool		udpate_win1;
	t_mini_map	mini_map;
	
	// PLAYER
	t_player	player;

	// MISC
	int			zoom;
}				t_game;
/*----------------  draw_rectangle.c  ---------------*/
int		draw_rectangle(t_game *game, int w, int h, int x, int y);

/*----------------  draw_square.c  ---------------*/
int		draw_square(t_game *game, int side, int x, int y);

/*----------------  draw_vertex.c  ---------------*/
int		draw_vertex(t_img *img, int x0, int y0, int x1, int y1);

/*----------------  optimization_helper.c  ---------------*/
void	img_pix_put(t_img *img, int x, int y, int color);

/*----------------  draw_minimap.c  ---------------*/
int		draw_minimap(t_game *game);

/*----------------  draw_rays.c  ---------------*/
int		draw_rays(t_game *game);

/*----------------  render_all.c  ---------------*/
int		render_all(t_game *game);

/*----------------  player_hooks.c  ---------------*/
int		move_player(t_game *game, int key);

/*----------------  close_game.c  ---------------*/
int		close_game(void *p);

/*----------------  key_hooks.c  ---------------*/
int		key_win1(int key, void *p);

/*----------------  mouse_hooks.c  ---------------*/
int		mouse_move_win1(int x, int y, void *p);
int		mouse_btn_win1(int key, void *p);

/*----------------  init_hooks.c  ---------------*/
void	init_hooks(t_game *game);

/*----------------  init_player_struct.c  ---------------*/
void	init_player(t_game *game);

/*----------------  init_map_struct.c  ---------------*/
int		init_map(t_game *game);

/*----------------  init_game_struct.c  ---------------*/
int		init_game(t_game **game);

/*----------------  init_minimap_struct.c  ---------------*/
void	init_minimap(t_game *game);

/*----------------  background.c  ---------------*/
int		rectangle(t_game *game, int w, int h, int x, int y);
int		fill_background(t_game *game);

# endif
