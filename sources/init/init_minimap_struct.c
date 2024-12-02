#include "../../includes/doomette.h"

void init_minimap(t_game *game)
{
	game->mini_map.img.mlx_img = NULL;
	game->mini_map.width = 150;
	game->mini_map.height = 150;
	game->mini_map.tile = MAP_TILE;
	game->mini_map.map_focus = false;
	game->mini_map.is_square = true;
}




