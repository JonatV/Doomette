#include "../../includes/doomette.h"

int close_game(void *p)
{
	t_game	*game;

	game = (t_game *)p;
	printf("Exiting...\n");
	mlx_clear_window(game->mlx, game->win1);
	mlx_destroy_image(game->mlx, game->img1);
	mlx_destroy_window(game->mlx, game->win1);
	free(game->mlx);
	free(game);
	exit(0);
}