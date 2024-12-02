#include "../../includes/doomette.h"

int	init_game(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (1);
	if (!((*game)->mlx = mlx_init()))
		return (1);
	if (!((*game)->win1 = mlx_new_window((*game)->mlx, WIN1_SX, WIN1_SY, TITLE)))
		return (1);
	init_map(*game);
	init_minimap(*game);
	init_player(*game);
	(*game)->udpate_win1 = true;
	(*game)->zoom = 0;
	prepare_background(*game);
	(*game)->game_screen.mlx_img = NULL;
	return 0;
}
