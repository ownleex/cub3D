
#include "cub3d.h"

/*
** Écrit un pixel de couleur dans l'image principale
** param game: Pointeur vers la structure principale du jeu
** param x: Coordonnée X du pixel à écrire
** param y: Coordonnée Y du pixel à écrire
** param color: Valeur de couleur RGB du pixel
*/
void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	// Vérifier que les coordonnées sont dans les limites de l'image
	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return;
	
	// Calculer l'adresse du pixel dans les données de l'image
	dst = game->img_addr + (y * game->img_line_length + x * (game->img_bits_per_pixel / 8));
	
	// Écrire la valeur de couleur RGB du pixel
	*(unsigned int*)dst = color;
}

/*
** Dessine le plafond et le sol pour une colonne de l'écran
** param game: Pointeur vers la structure principale du jeu
** param x: Coordonnée X de la colonne
** param ray: Pointeur vers la structure de rayon
*/
void	draw_ceiling_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	// Dessiner le plafond (de haut en bas jusqu'au début du mur)
	for (y = 0; y < ray->draw_start; y++)
		put_pixel_to_img(game, x, y, game->tex.ceiling);
	
	// Dessiner le sol (de la fin du mur jusqu'en bas de l'écran)
	for (y = ray->draw_end + 1; y < WINDOW_HEIGHT; y++)
		put_pixel_to_img(game, x, y, game->tex.floor);
}

/*
** Dessine un mur texturé pour une colonne de l'écran
** param game: Pointeur vers la structure principale du jeu
** param x: Coordonnée X de la colonne
** param ray: Pointeur vers la structure de rayon
*/
void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	// Sélectionner la texture appropriée en fonction de l'orientation du mur
	tex = select_texture(game, ray);
	
	// Calculer l'incrément de la coordonnée de texture par pixel de l'écran
	step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	
	// Position de texture initiale
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	
	// Dessiner le mur du haut vers le bas
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		// Convertir la position de texture en coordonnée Y entière
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		
		// Récupérer la couleur du pixel dans la texture
		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		
		// Écrire le pixel dans l'image
		put_pixel_to_img(game, x, y, color);
		y++;
	}
}

/*
** Dessine une ligne verticale complète (plafond, mur, sol) pour une colonne de l'écran
** param game: Pointeur vers la structure principale du jeu
** param x: Coordonnée X de la colonne
** param ray: Pointeur vers la structure de rayon
*/
void	draw_vertical_line(t_game *game, int x, t_ray *ray)
{
	// Dessiner le plafond et le sol
	draw_ceiling_floor(game, x, ray);
	
	// Dessiner le mur texturé
	draw_textured_wall(game, x, ray);
}

/*
** Fonction principale de rendu appelée à chaque image
** param game: Pointeur vers la structure principale du jeu
** return: Toujours 0
*/
int	render(t_game *game)
{
	// Effacer l'image (remplir de zéros)
	ft_memset(game->img_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * (game->img_bits_per_pixel / 8));
		// ou avec :
	//mlx_clear_window(game->mlx, game->win);
	
	// Effectuer le raycasting pour calculer ce qui doit être affiché
	raycasting(game);
	
	// Afficher l'image à l'écran
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	
	return (0);
}