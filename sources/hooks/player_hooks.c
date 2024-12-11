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
	// saved the key state
	if (key == XK_w)
		game->key_list.w = true;
	if (key == XK_s)
		game->key_list.s = true;
	if (key == XK_a)
		game->key_list.a = true;
	if (key == XK_d)
		game->key_list.d = true;
	if (key == XK_e)
	{
		//todo open the door
	}
	// printf("player x = %f, y = %f, pa = %f\n", game->player.x, game->player.y, game->player.pa);
	return (0);
}

void	rotate_player(t_game *game, float rot_speed)
{
	game->player.pa += rot_speed;
	if (game->player.pa < 0)
		game->player.pa += 2 * PI;
	if (game->player.pa > 2 * PI)
		game->player.pa -= 2 * PI;
	game->player.pdx = cos(game->player.pa);
	game->player.pdy = sin(game->player.pa);
}

int	update_player(t_game *game)
{
	if (game->key_list.w || game->key_list.s || game->key_list.a || game->key_list.d)
	{
		float x = game->player.x;
		float y = game->player.y;
		int tile_size = game->mini_map.tile;

		// Get the current time and elapsed time
		// double current_time = get_time();
		// double delta_time = current_time - game->last_time;
		// game->last_time = current_time;

		// if (delta_time > 0.15)
		// 	delta_time = 0.15;

		// Calculate the player movement speed
		float base_move_speed = 100.0;
		float base_rot_speed = 3.0;
		float move_speed = base_move_speed * game->delta_time;
		float rot_speed = base_rot_speed * game->delta_time;

		if (game->key_list.a)
		{
			rotate_player(game, -rot_speed);
			// game->player.pa -= rot_speed;
			// if (game->player.pa < 0)
			// 	game->player.pa += 2 * PI;
			// game->player.pdx = cos(game->player.pa) * move_speed;
			// game->player.pdy = sin(game->player.pa) * move_speed;
		}
		if (game->key_list.d)
		{
			rotate_player(game, rot_speed);
			// game->player.pa += rot_speed;
			// if (game->player.pa > 2 * PI)
			// 	game->player.pa -= 2 * PI;
			// game->player.pdx = cos(game->player.pa) * move_speed;
			// game->player.pdy = sin(game->player.pa) * move_speed;
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
	}
	printf("player x = %f, y = %f, pa = %f\n", game->player.x, game->player.y, game->player.pa);
	return (0);
}
