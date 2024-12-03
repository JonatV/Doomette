#include "../../includes/doomette.h"

int move_release_player(t_game *game, int key)
{
	if (key==XK_w)
		game->key_list.w = false;
	if (key==XK_a)
		game->key_list.a = false;
	if (key==XK_s)
		game->key_list.s = false;
	if (key==XK_d)
		game->key_list.d = false;
	return (0);
}

int move_press_player(t_game *game, int key)
{
	float x = game->player.x;
	float y = game->player.y;
	// int tile_size = MAP_TILE + game->zoom;//wip
	int tile_size = game->mini_map.tile;

	if (key == XK_Up)
	{
		if (game->map[(int)(y - PLAYER_SPEED) / tile_size][(int)x / tile_size] == 0)
			game->player.y = game->player.y - PLAYER_SPEED;
	}
	if (key == XK_Down)
	{
		if (game->map[(int)(y + PLAYER_SPEED + PLAYER_SIZE/2) / tile_size][(int)x / tile_size] == 0)
			game->player.y = game->player.y + PLAYER_SPEED;
	}
	if (key == XK_Left)
	{
		if (game->map[(int)y / tile_size][(int)(x - PLAYER_SPEED) / tile_size] == 0)
			game->player.x = game->player.x - PLAYER_SPEED;
	}
	if (key == XK_Right)
	{
		if (game->map[(int)y / tile_size][(int)(x + PLAYER_SPEED + PLAYER_SIZE/2) / tile_size] == 0)
			game->player.x = game->player.x + PLAYER_SPEED;
	}
	// saved the key state
	if (key == XK_w)
		game->key_list.w = true;
	if (key == XK_s)
		game->key_list.s = true;
	if (key == XK_a)
		game->key_list.a = true;
	if (key == XK_d)
		game->key_list.d = true;
	printf("player x = %f, y = %f, pa = %f\n", game->player.x, game->player.y, game->player.pa);
	return (0);
}

int	update_player(t_game *game)
{
	float x = game->player.x;
	float y = game->player.y;
	int tile_size = game->mini_map.tile;

	// Get the current time and elapsed time
	double current_time = get_time();
	double delta_time = current_time - game->last_time;
	game->last_time = current_time;

	if (delta_time > 0.15)
		delta_time = 0.15;

	// Calculate the player movement speed
	float base_move_speed = 100.0;
	float base_rot_speed = 2.0;
	float move_speed = base_move_speed * delta_time;
	float rot_speed = base_rot_speed * delta_time;

	if (game->key_list.a)
	{
		game->player.pa -= rot_speed;
		if (game->player.pa < 0)
			game->player.pa += 2 * PI;
		game->player.pdx = cos(game->player.pa) * move_speed;
		game->player.pdy = sin(game->player.pa) * move_speed;
	}
	if (game->key_list.d)
	{
		game->player.pa += rot_speed;
		if (game->player.pa > 2 * PI)
			game->player.pa -= 2 * PI;
		game->player.pdx = cos(game->player.pa) * move_speed;
		game->player.pdy = sin(game->player.pa) * move_speed;
	}
	int xo = (game->player.pdx < 0) ? -5 : 5;
	int yo = (game->player.pdy < 0) ? -5 : 5;

	if (game->key_list.w)
	{
		if (game->map[(int)y / tile_size][(int)(x + xo) / tile_size] == 0)
		{
			game->player.x += game->player.pdx * move_speed;
		}
		if (game->map[(int)(y + yo) / tile_size][(int)x / tile_size] == 0)
		{
			game->player.y += game->player.pdy * move_speed;
		}
	}
	if (game->key_list.s)
	{
		if (game->map[(int)y / tile_size][(int)(x - xo) / tile_size] == 0)
		{
			game->player.x -= game->player.pdx * move_speed;
		}
		if (game->map[(int)(y - yo) / tile_size][(int)x / tile_size] == 0)
		{
			game->player.y -= game->player.pdy * move_speed;
		}
	}
	printf("player x = %f, y = %f, pa = %f\n", game->player.x, game->player.y, game->player.pa);
	return (0);
}
