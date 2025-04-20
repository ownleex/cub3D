
#include "cub3d.h"

/*
** Initialise la connexion MLX, la fenêtre et l'image principale
** param game: Pointeur vers la structure principale du jeu
** return: true si l'initialisation a réussi, false sinon
*/
bool	init_mlx(t_game *game)
{
	int	i;

	// Initialiser le tableau d'état des touches à 0
	i = 0;
	while (i < 128)
	{
		game->keys[i] = 0;
		i++;
	}
	
	// Initialiser les états des touches de direction
	game->key_left = 0;
	game->key_right = 0;
	
	// Initialiser la connexion MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	
	// Créer la fenêtre du jeu
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (false);
	
	// Créer l'image principale pour le rendu
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (false);
	
	// Récupérer l'adresse des données de l'image principale
	game->img_addr = mlx_get_data_addr(game->img, &game->img_bits_per_pixel,
			&game->img_line_length, &game->img_endian);
	
	return (true);
}

/*
** Vérifie que le joueur a été correctement initialisé avec une direction valide
** param game: Pointeur vers la structure principale du jeu
** return: true si le joueur est correctement initialisé
*/
bool	init_player(t_game *game)
{
	// Vérifier que la direction du joueur est valide (non nulle)
	if (game->player.dir.x == 0 && game->player.dir.y == 0)
		return (false);
	
	// Vérifier que le plan de caméra est valide (non nul)
	if (game->player.plane.x == 0 && game->player.plane.y == 0)
		return (false);
		
	return (true);
}