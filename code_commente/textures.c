
#include "cub3d.h"

/*
** Récupère la valeur d'un pixel dans une texture
** param texture: Pointeur vers la structure de texture
** param x: Coordonnée X du pixel dans la texture
** param y: Coordonnée Y du pixel dans la texture
** return: Valeur de couleur RGB du pixel
*/
int	get_tex_pixel(t_texture *texture, int x, int y)
{
	char	*dst;

	// Vérifier que les coordonnées sont dans les limites de la texture
	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	
	// Calculer l'adresse du pixel dans les données de l'image
	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	
	// Retourner la valeur de couleur RGB du pixel
	return (*(unsigned int*)dst);
}

/*
** Sélectionne la texture appropriée en fonction de l'orientation du mur touché
** param game: Pointeur vers la structure principale du jeu
** param ray: Pointeur vers la structure de rayon
** return: Pointeur vers la texture à utiliser
*/
t_texture	*select_texture(t_game *game, t_ray *ray)
{
	// Sélectionner la texture en fonction de l'orientation du mur
	if (ray->side == 0) // Un mur vertical a été touché (côté X)
	{
		if (ray->step.x < 0) // Le rayon regarde vers l'ouest (X négatif)
			return (&game->tex.west);
		else // Le rayon regarde vers l'est (X positif)
			return (&game->tex.east);
	}
	else // Un mur horizontal a été touché (côté Y)
	{
		if (ray->step.y < 0) // Le rayon regarde vers le nord (Y négatif)
			return (&game->tex.north);
		else // Le rayon regarde vers le sud (Y positif)
			return (&game->tex.south);
	}
}