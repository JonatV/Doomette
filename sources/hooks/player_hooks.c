#include "../../includes/doomette.h"

int move_player(t_game *game, int key)
{
	int x = game->player.x;
	int y = game->player.y;

	if (key == XK_Up || key == XK_w)
	{
		if (game->map[y - 1][x] == 0)
			game->player.y--;
	}
	if (key == XK_Down || key == XK_s)
	{
		if (game->map[y + 1][x] == 0)
			game->player.y++;
	}
	if (key == XK_Left)
	{
		if (game->map[y][x - 1] == 0)
			game->player.x--;
	}
	if (key == XK_Right)
	{
		if (game->map[y][x + 1] == 0)
			game->player.x++;
	}
	return (0);
}
