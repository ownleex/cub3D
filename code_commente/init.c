
#include "cub3d.h"

/*
** Crée une nouvelle texture de dimensions spécifiées
** param game: Pointeur vers la structure principale du jeu
** param texture: Pointeur vers la structure de texture à initialiser
** param width: Largeur de la texture en pixels
** param height: Hauteur de la texture en pixels
** return: true si la création a réussi, false sinon
*/
bool	create_texture(t_game *game, t_texture *texture, int width, int height)
{
	// Créer une nouvelle image MLX
	texture->img = mlx_new_image(game->mlx, width, height);
	if (!texture->img)
		return (false);
	
	// Récupérer l'adresse des données de l'image
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	
	// Stocker les dimensions de la texture
	texture->width = width;
	texture->height = height;
	return (true);
}

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
** Initialise les données des textures (murs nord, sud, est, ouest)
** param game: Pointeur vers la structure principale du jeu
** return: true si l'initialisation a réussi, false sinon
*/
bool	init_texture_data(t_game *game)
{
	bool	success;

	// Analyser les textures depuis le fichier de configuration
	success = true;
	if (!parse_textures(game))
		success = false;
	
	// Mettre à jour l'état des textures
	game->textures_loaded = success;
	
	return (success);
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