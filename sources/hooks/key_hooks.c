#include "../../includes/doomette.h"

int	key_win1(int key, void *p)
{
	t_game	*game;

	game = (t_game *)p;
	printf("Key in Win1 : %x\n",key);
	if (key==XK_space) // exit game
		mlx_clear_window(game->mlx, game->win1);
	if (key==XK_Escape) // exit game
		close_game(game);
	return (0);
}
