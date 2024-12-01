#include "../../includes/doomette.h"

int move_player(t_game *game, int key)
{
	float x = game->player.x;
	float y = game->player.y;
	// int tile_size = MAP_TILE + game->zoom;//wip
	int tile_size = game->tile;

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
	if (key==XK_a)
	{
		game->player.pa -= 0.1;
		if (game->player.pa < 0)
			game->player.pa += 2 * PI;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	if (key==XK_d)
	{
		game->player.pa += 0.1;
		if (game->player.pa > 2 * PI)
			game->player.pa -= 2 * PI;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	if (key==XK_w)
	{
		if (game->map[(int)(y + game->player.pdy) / tile_size][(int)(x + game->player.pdx) / tile_size] == 0)
		{
			game->player.x = game->player.x + game->player.pdx;
			game->player.y = game->player.y + game->player.pdy;
		}
	}
	if (key==XK_s)
	{
		if (game->map[(int)(y - game->player.pdy) / tile_size][(int)(x - game->player.pdx) / tile_size] == 0)
		{
			game->player.x = game->player.x - game->player.pdx;
			game->player.y = game->player.y - game->player.pdy;
		}
	}
	printf("player x = %f, y = %f, pa = %f\n", game->player.x, game->player.y, game->player.pa);
	return (0);
}
