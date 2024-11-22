#include "../../includes/doomette.h"

int	key_win1(int key, void *p)
{
	t_game	*game;

	game = (t_game *)p;
	printf("Key in Win1 : %d\n",key);
	if (key==0xFF1B) // exit game
		close_game(game);
	return (0);
}
