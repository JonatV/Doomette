#include "../../includes/doomette.h"

int render_all(t_game *game)
{
	update_player(game);
	draw_minimap(game);
	return (0);
}
