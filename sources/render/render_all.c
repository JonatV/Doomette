#include "../../includes/doomette.h"

int render_all(t_game *game)
{
	// fps
	printf("FPS: %f\n", 1 / (get_time() - game->last_time));
	update_player(game);
	draw_minimap(game);
	return (0);
}
