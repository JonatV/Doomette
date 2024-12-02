#include "../../includes/doomette.h"

void	init_player(t_game *game)
{
	for (int i = 0; i < MAP_W; i++)
	{
		for (int j = 0; j < MAP_H; j++)
		{
			if (game->map[i][j] == 2)
			{
				game->player.x = j * game->mini_map.tile + game->mini_map.tile / 2;
				game->player.y = i * game->mini_map.tile + game->mini_map.tile / 2;
				game->map[i][j] = 0;
			}
		}
	}
	game->player.pa = 0;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
	game->player.size = PLAYER_SIZE;
	game->player.dir = NORTH;
}
