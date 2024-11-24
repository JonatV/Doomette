#include "../../includes/doomette.h"

int init_map(t_game *game)
{
	game->mini_map.mlx_img = NULL;
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
	// int temp_map[MAP_W][MAP_H] = {
	// 	#define MAP_W 24
	// 	#define MAP_H 24
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };

	int temp_map[MAP_H][MAP_W] = {
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,1,0,0,0,0,2,1},
		{1,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1},
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
			if (game->map[i][j] == 2)
			{
				game->player.x = j * MAP_TILE;
				game->player.y = i * MAP_TILE;
				game->player.dir = NORTH;
				game->player.size = PLAYER_SIZE;
				game->map[i][j] = 0;
			}
		}
	}
	return (0);
}
