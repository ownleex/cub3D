
#include "cub3d.h"

/*
** Libère la mémoire du tableau de lignes du fichier
** param game: Pointeur vers la structure principale du jeu
*/
void	free_file(t_game *game)
{
	int	i;

	// Vérifier que le tableau de lignes existe
	if (!game->file)
		return ;
	
	// Libérer chaque ligne
	i = 0;
	while (game->file[i])
	{
		free(game->file[i]);
		i++;
	}
	
	// Libérer le tableau lui-même
	free(game->file);
	game->file = NULL;
}

/*
** Libère la mémoire de la carte
** param game: Pointeur vers la structure principale du jeu
*/
void	free_map(t_game *game)
{
	int	i;

	// Vérifier que la carte existe
	if (!game->map)
		return ;
	
	// Libérer chaque ligne de la carte
	i = 0;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	
	// Libérer le tableau de la carte
	free(game->map);
	game->map = NULL;
}

/*
** Libère la mémoire des textures
** param game: Pointeur vers la structure principale du jeu
*/
void	free_textures(t_game *game)
{
	// Libérer les images de texture si elles existent
	if (game->tex.north.img)
		mlx_destroy_image(game->mlx, game->tex.north.img);
	if (game->tex.south.img)
		mlx_destroy_image(game->mlx, game->tex.south.img);
	if (game->tex.east.img)
		mlx_destroy_image(game->mlx, game->tex.east.img);
	if (game->tex.west.img)
		mlx_destroy_image(game->mlx, game->tex.west.img);
}

/*
** Libère la mémoire des ressources MLX
** param game: Pointeur vers la structure principale du jeu
*/
void	free_mlx(t_game *game)
{
	// Libérer l'image principale si elle existe
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	
	// Libérer la fenêtre si elle existe
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	
	// Libérer la connexion MLX si elle existe
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/*
** Fonction appelée lors de la fermeture de la fenêtre
** param game: Pointeur vers la structure principale du jeu
** return: Toujours 0
*/
int	exit_hook(t_game *game)
{
	// Libérer toutes les ressources et quitter proprement
	clean_exit(game, EXIT_SUCCESS);
	return (0);
}

/*
** Libère toutes les ressources et quitte le programme
** param game: Pointeur vers la structure principale du jeu
** param status: Code de sortie
*/
void	clean_exit(t_game *game, int status)
{
	// Libérer le tableau de lignes du fichier
	free_file(game);
	
	// Libérer la carte
	free_map(game);
	
	// Libérer les textures
	free_textures(game);
	
	// Libérer les ressources MLX
	free_mlx(game);
	
	// Quitter le programme avec le code de sortie spécifié
	exit(status);
}