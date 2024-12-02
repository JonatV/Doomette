#include "includes/doomette.h"

int	main(void)
{
	t_game	*game;

	// init game struct
	init_game(&game);
	// load xpm
	if (!(game->mossy_brick.img = mlx_xpm_file_to_image(game->mlx, "assets/textures_xpm/mossy_brick.xpm", &game->mossy_brick.x, &game->mossy_brick.y)))
		return (1);
	// add xpm to the window
	for (int i = 0; i < WIN1_SX - game->mossy_brick.x; i += game->mossy_brick.x)
		mlx_put_image_to_window(game->mlx, game->win1, game->mossy_brick.img, i, i);
	sleep(2);
	init_hooks(game);
	mlx_loop(game->mlx);
	return 0;
}
