#include "../../includes/doomette.h"

int move_player(t_game *game, int key)
{
	float x = game->player.x;
	float y = game->player.y;

	if (key == XK_Up)
	{
		if (game->map[(int)(y - PLAYER_SPEED) / MAP_TILE][(int)x / MAP_TILE] == 0)
			game->player.y = game->player.y - PLAYER_SPEED;
	}
	if (key == XK_Down)
	{
		if (game->map[(int)(y + PLAYER_SPEED + PLAYER_SIZE/2) / MAP_TILE][(int)x / MAP_TILE] == 0)
			game->player.y = game->player.y + PLAYER_SPEED;
	}
	if (key == XK_Left)
	{
		if (game->map[(int)y / MAP_TILE][(int)(x - PLAYER_SPEED) / MAP_TILE] == 0)
			game->player.x = game->player.x - PLAYER_SPEED;
	}
	if (key == XK_Right)
	{
		if (game->map[(int)y / MAP_TILE][(int)(x + PLAYER_SPEED + PLAYER_SIZE/2) / MAP_TILE] == 0)
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
		if (game->map[(int)(y + game->player.pdy) / MAP_TILE][(int)(x + game->player.pdx) / MAP_TILE] == 0)
		{
			game->player.x = game->player.x + game->player.pdx;
			game->player.y = game->player.y + game->player.pdy;
		}
	}
	if (key==XK_s)
	{
		if (game->map[(int)(y - game->player.pdy) / MAP_TILE][(int)(x - game->player.pdx) / MAP_TILE] == 0)
		{
			game->player.x = game->player.x - game->player.pdx;
			game->player.y = game->player.y - game->player.pdy;
		}
	}
	return (0);
}
