#include "../../includes/doomette.h"

int move_player(t_game *game, int key)
{
	int x = game->player.x;
	int y = game->player.y;

	if (key == XK_Up || key == XK_w)
	{
		if (game->map[(y - PLAYER_SPEED) / MAP_TILE][x / MAP_TILE] == 0)
			game->player.y = game->player.y - PLAYER_SPEED;
	}
	if (key == XK_Down || key == XK_s)
	{
		if (game->map[(y + PLAYER_SPEED + PLAYER_SIZE/2) / MAP_TILE][x / MAP_TILE] == 0)
			game->player.y = game->player.y + PLAYER_SPEED;
	}
	if (key == XK_Left)
	{
		if (game->map[y / MAP_TILE][(x - PLAYER_SPEED) / MAP_TILE] == 0)
			game->player.x = game->player.x - PLAYER_SPEED;
	}
	if (key == XK_Right)
	{
		if (game->map[y / MAP_TILE][(x + PLAYER_SPEED + PLAYER_SIZE/2) / MAP_TILE] == 0)
			game->player.x = game->player.x + PLAYER_SPEED;
	}
	if (key==XK_a)
	{
		game->player.dir--;
		if (game->player.dir == -1)
			game->player.dir = 3;
	}
	if (key==XK_d)
	{
		game->player.dir++;
		if (game->player.dir == 4)
			game->player.dir = 0;
	}
	return (0);
}
