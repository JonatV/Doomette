#include "../../includes/doomette.h"

int init_map(t_game *game)
{
	game->map = malloc(sizeof(int *) * MAP_W);
	if (!game->map)
		return (1);
	for (int i = 0; i < MAP_W; i++)
	{
		game->map[i] = malloc(sizeof(int) * MAP_H);
		if (!game->map[i])
		{
			for (int j = 0; j < i; j++)
				free(game->map[j]);
			free(game->map);
			return (1);
		}
	}
	int temp_map[MAP_H][MAP_W] = {
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,1},
		{1,0,0,1,1,1,1,1,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,0,0,1},
		{1,0,0,1,1,1,1,1,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int i = 0; i < MAP_W; i++)
	{
		for (int j = 0; j < MAP_H; j++)
		{
			game->map[i][j] = temp_map[i][j];
		}
	}
	return (0);
}