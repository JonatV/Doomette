#include "../../includes/doomette.h"

int	key_press_win1(int key, void *p)
{
	t_game	*game;

	game = (t_game *)p;
	game->update_win1 = true;
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
	move_press_player(game, key);
	if (key==XK_1)
	{
		game->mini_map.is_square = !game->mini_map.is_square;
		game->mini_map.map_focus = false;
	}
	if (key==XK_space) // toggle map focus
	{
		game->mini_map.map_focus = !game->mini_map.map_focus;
	}
	if (key==XK_Escape) // exit game
		close_game(game);
	return (0);
}

int	key_release_win1(int key, void *p)
{
	t_game	*game;

	game = (t_game *)p;
	game->update_win1 = false;
	printf("Key released in Win1 : %x\n",key);
	move_release_player(game, key);
	return (0);
}
