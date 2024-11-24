#include "../../includes/doomette.h"

int	key_win1(int key, void *p)
{
	t_game	*game;

	game = (t_game *)p;
	printf("Key in Win1 : %x\n",key);
	if (key==XK_comma)
	{
		game->zoom--;
		printf("ZOOM = [%d] TILESIZE = [%d]\n", game->zoom, (game->zoom * MAP_TILE)/MAP_H);
	}
	if (key==XK_period)
	{
		game->zoom++;
		printf("ZOOM = [%d] TILESIZE = [%d]\n", game->zoom, (game->zoom * MAP_TILE)/MAP_H);
	}
	move_player(game, key);
	if (key==XK_1)
		rectangle(game, 200, 200, 0, 0);
	if (key==XK_space) // exit game
		mlx_clear_window(game->mlx, game->win1);
	if (key==XK_Escape) // exit game
		close_game(game);
	return (0);
}
