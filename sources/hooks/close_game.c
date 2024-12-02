#include "../../includes/doomette.h"

int close_game(void *p)
{
	t_game	*game;

	game = (t_game *)p;
	mlx_clear_window(game->mlx, game->win1);
	mlx_destroy_window(game->mlx, game->win1);
	mlx_destroy_image(game->mlx, game->mossy_brick.img);
	mlx_destroy_image(game->mlx, game->mini_map.img.mlx_img);
	mlx_destroy_image(game->mlx, game->game_screen.mlx_img);
	mlx_destroy_image(game->mlx, game->bg.mlx_img);

	for (int i = 0; i < MAP_W; i++)
		free(game->map[i]);
	free(game->map);

	free(game->mlx);
	free(game);

	printf("Exiting\n");
	exit(0);
}
