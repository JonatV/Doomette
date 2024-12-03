#include "../../includes/doomette.h"

static void compute_max_focus_minimap(t_game *game)
{
	float	h;
	float	w;

	h = game->mini_map.max_focus_height;
	w = game->mini_map.max_focus_width;
	while (h > WIN1_SY - INNER_BORDER * 2)
	{
		game->mini_map.focus_tile--;
		h = MAP_H * game->mini_map.focus_tile;
		w = MAP_W * game->mini_map.focus_tile;
	}
	while (w > WIN1_SX - INNER_BORDER * 2)
	{
		game->mini_map.focus_tile--;
		w = MAP_W * game->mini_map.focus_tile;
		h = MAP_H * game->mini_map.focus_tile;
	}
	game->mini_map.max_focus_height = h;
	game->mini_map.max_focus_width = w;
}

void init_minimap(t_game *game)
{
	game->mini_map.img.mlx_img = NULL;
	game->mini_map.width = 150;
	game->mini_map.height = 150;
	game->mini_map.tile = MAP_TILE;
	game->mini_map.map_focus = false;
	game->mini_map.is_square = true;
	// compute the max focus map size
	game->mini_map.max_focus_width = MAP_W * game->mini_map.tile;
	game->mini_map.max_focus_height = MAP_H * game->mini_map.tile;
	game->mini_map.focus_tile = MAP_TILE;
	compute_max_focus_minimap(game);
}




