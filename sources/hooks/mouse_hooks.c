#include "../../includes/doomette.h"

int	mouse_move_win1(int x, int y, void *p)
{
	(void)p;
	(void)x;
	(void)y;
	t_game	*game;

	game = p;

	// Calculate the player rotation speed
	float base_rot_speed = 1.0;
	float rot_speed = base_rot_speed * game->delta_time; 
	if (x < WIN1_X_CENTER)
		rotate_player(game, -rot_speed);
	if (x > WIN1_X_CENTER)
		rotate_player(game, rot_speed);
	// printf("player x vision[%f]\n", game->player.pdx); //dev
	printf("mouse x[%d]\n", x); //dev
	return (0);
}

int	mouse_btn_win1(int key, void *p)
{
	(void)p;
	// update_win1 = true;
	printf("Mouse in Win1, button %d.\n", key);
	return (0);
}
