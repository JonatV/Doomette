#include "includes/doomette.h"

int	main(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	// xpm sizes
	int	xpm1_x;
	int	xpm1_y;


	if (!(game->mlx = mlx_init()))
		return (1);
	if (!(game->win1 = mlx_new_window(game->mlx, WIN1_SX, WIN1_SY, TITLE)))
		return (1);
	if (!(game->img1 = mlx_xpm_file_to_image(game->mlx, "assets/textures_xpm/mossy_brick.xpm", &xpm1_x, &xpm1_y)))
		return (1);
	for (int i = 0; i < WIN1_SX - xpm1_x; i += xpm1_x)
		mlx_put_image_to_window(game->mlx, game->win1, game->img1, i, 0);
	sleep(1);

	init_hooks(game);
	mlx_loop(game->mlx);
	return 0;
}
