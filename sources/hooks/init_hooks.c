#include "../../includes/doomette.h"

// Install hooks
void init_hooks(t_game *game)
{
	mlx_hook(game->win1, KeyPress, KeyPressMask, key_win1, game);
	mlx_mouse_hook(game->win1, mouse_btn_win1, game);
	mlx_hook(game->win1, MotionNotify, PointerMotionMask, mouse_move_win1, game); // 6, (1L<<6)
	mlx_hook(game->win1, ClientMessage, StructureNotifyMask, close_game, game); //33, (1L<<17)
	mlx_loop_hook(game->mlx, &draw_map, game); // dev
	// mlx_loop_hook(game->mlx, &fill_background, game); // dev
}
