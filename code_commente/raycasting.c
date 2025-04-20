
#include "cub3d.h"

/*
** Calcule la position et la direction d'un rayon pour une colonne de l'écran
** param game: Pointeur vers la structure principale du jeu
** param ray: Pointeur vers la structure de rayon à remplir
** param x: Coordonnée X de la colonne de l'écran (de 0 à WINDOW_WIDTH-1)
*/
void	calculate_ray_pos_dir(t_game *game, t_ray *ray, int x)
{
	// Calculer la coordonnée x dans l'espace de la caméra
	// (de -1 à gauche de l'écran à +1 à droite)
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	
	// Calculer la direction du rayon
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	
	// Déterminer la case de la carte où se trouve le joueur
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	
	// Calculer la longueur du rayon d'une case x ou y à la suivante
	// Éviter la division par zéro
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

/*
** Calcule les pas et distances initiales pour l'algorithme DDA
** param game: Pointeur vers la structure principale du jeu
** param ray: Pointeur vers la structure de rayon
*/
void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	// Calculer le pas et la distance initiale en x
	if (ray->dir.x < 0)
	{
		// Si le rayon pointe vers la gauche
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		// Si le rayon pointe vers la droite
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	
	// Calculer le pas et la distance initiale en y
	if (ray->dir.y < 0)
	{
		// Si le rayon pointe vers le haut
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		// Si le rayon pointe vers le bas
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}

/*
** Exécute l'algorithme DDA (Digital Differential Analysis) pour trouver un mur
** param game: Pointeur vers la structure principale du jeu
** param ray: Pointeur vers la structure de rayon
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	
	// Exécuter l'algorithme DDA jusqu'à ce qu'un mur soit touché
	while (!hit)
	{
		// Passer à la case suivante, soit en x, soit en y (celle qui est la plus proche)
		if (ray->side_dist.x < ray->side_dist.y)
		{
			// Le rayon passe à la case suivante en x
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step.x;
			ray->side = 0; // Un mur vertical a été touché (côté X)
		}
		else
		{
			// Le rayon passe à la case suivante en y
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step.y;
			ray->side = 1; // Un mur horizontal a été touché (côté Y)
		}
		
		// Vérifier si le rayon a touché un mur
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
	
	// Calculer la distance projetée sur la direction de la caméra
	// pour éviter l'effet "fisheye"
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x + 
							(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y + 
							(1 - ray->step.y) / 2) / ray->dir.y;
}

/*
** Calcule la hauteur de la ligne verticale à dessiner pour un mur
** param ray: Pointeur vers la structure de rayon
*/
void	calculate_wall_height(t_ray *ray)
{
	// Sécuriser la distance projetée (évite les divisions par zéro ou les valeurs négatives)
	if (ray->perp_wall_dist < 0.000001)
		ray->perp_wall_dist = 0.000001;

	// Calculer la hauteur de la ligne à dessiner
	// Plus le mur est loin, plus la ligne est courte
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);

	// Déterminer le début de la ligne verticale à dessiner
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;

	// Déterminer la fin de la ligne verticale à dessiner
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

/*
** Calcule les coordonnées de texture pour un mur
** param game: Pointeur vers la structure principale du jeu
** param ray: Pointeur vers la structure de rayon
*/
void	calculate_texture_x(t_game *game, t_ray *ray)
{
	double	wall_x;
	
	// Calculer la valeur exacte où le rayon a touché le mur
	if (ray->side == 0)
		wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	
	// Ne garder que la partie fractionnaire
	wall_x -= floor(wall_x);
	ray->wall_x = wall_x;
	
	// Convertir en coordonnée X de texture
	ray->tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	
	// Inverser la texture si le rayon touche le mur de "l'intérieur"
	if ((ray->side == 0 && ray->dir.x > 0) || 
		(ray->side == 1 && ray->dir.y < 0))
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
}

/*
** Fonction principale de raycasting, appelée à chaque image
** param game: Pointeur vers la structure principale du jeu
*/
void	raycasting(t_game *game)
{
	int	x;
	
	// Pour chaque colonne de l'écran
	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		// Calculer la position et la direction du rayon
		calculate_ray_pos_dir(game, &game->ray, x);
		
		// Calculer les pas et distances initiales
		calculate_step_and_side_dist(game, &game->ray);
		
		// Exécuter l'algorithme DDA pour trouver un mur
		perform_dda(game, &game->ray);
		
		// Calculer la hauteur du mur à l'écran
		calculate_wall_height(&game->ray);
		
		// Calculer les coordonnées de texture
		calculate_texture_x(game, &game->ray);
		
		// Dessiner la colonne
		draw_vertical_line(game, x, &game->ray);
	}
}