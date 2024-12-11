#include "../../includes/doomette.h"

int render_all(t_game *game)
{
	// fps
	printf("FPS: %f\n", 1 / (get_time() - game->last_time));
	update_player(game);
	draw_minimap(game);
	mlx_mouse_move(game->mlx, game->win1, WIN1_X_CENTER, WIN1_Y_CENTER);
	return (0);
}
