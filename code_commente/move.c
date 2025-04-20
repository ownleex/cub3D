
#include "cub3d.h"

/*
** Vérifie si une case est un mur extérieur de la carte
** param game: Pointeur vers la structure principale du jeu
** param x: Coordonnée X de la case à vérifier
** param y: Coordonnée Y de la case à vérifier
** return: true si la case est un mur extérieur, false sinon
*/
bool	is_exterior_wall(t_game *game, int x, int y)
{
	// Vérifier si la case est sur le bord de la carte
	if (x == 0 || y == 0 || x == game->map_width - 1 || y == game->map_height - 1)
		return (true);
	
	// Vérifier si une des cases adjacentes est un espace vide (hors carte)
	if (x > 0 && game->map[y][x - 1] == ' ')
		return (true);
	if (x < game->map_width - 1 && game->map[y][x + 1] == ' ')
		return (true);
	if (y > 0 && game->map[y - 1][x] == ' ')
		return (true);
	if (y < game->map_height - 1 && game->map[y + 1][x] == ' ')
		return (true);
	
	// Ce n'est pas un mur extérieur
	return (false);
}

/*
** Déplace le joueur vers l'avant
** param game: Pointeur vers la structure principale du jeu
*/
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	// Calculer les nouvelles coordonnées potentielles
	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	
	// Convertir en coordonnées de la carte
	map_x = (int)new_x;
	map_y = (int)new_y;
	
	// Vérifier si la nouvelle position est un mur
	if (game->map[map_y][map_x] == '1')
	{
		// Si c'est un mur extérieur, ne pas autoriser le mouvement
		if (is_exterior_wall(game, map_x, map_y))
			return;
	}
	
	// Mettre à jour la position du joueur
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers l'arrière
** param game: Pointeur vers la structure principale du jeu
*/
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	// Calculer les nouvelles coordonnées potentielles (direction inverse)
	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	
	// Convertir en coordonnées de la carte
	map_x = (int)new_x;
	map_y = (int)new_y;
	
	// Vérifier si la nouvelle position est un mur
	if (game->map[map_y][map_x] == '1')
	{
		// Si c'est un mur extérieur, ne pas autoriser le mouvement
		if (is_exterior_wall(game, map_x, map_y))
			return;
	}
	
	// Mettre à jour la position du joueur
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers la gauche (perpendiculairement à la direction)
** param game: Pointeur vers la structure principale du jeu
*/
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	// Calculer les nouvelles coordonnées potentielles (perpendiculaire à la direction)
	// Note: Pour aller à gauche, on utilise (dir.y, -dir.x) qui est perpendiculaire à (dir.x, dir.y)
	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	
	// Convertir en coordonnées de la carte
	map_x = (int)new_x;
	map_y = (int)new_y;
	
	// Vérifier si la nouvelle position est un mur
	if (game->map[map_y][map_x] == '1')
	{
		// Si c'est un mur extérieur, ne pas autoriser le mouvement
		if (is_exterior_wall(game, map_x, map_y))
			return;
	}
	
	// Mettre à jour la position du joueur
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers la droite (perpendiculairement à la direction)
** param game: Pointeur vers la structure principale du jeu
*/
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	// Calculer les nouvelles coordonnées potentielles (perpendiculaire à la direction)
	// Note: Pour aller à droite, on utilise (-dir.y, dir.x) qui est perpendiculaire à (dir.x, dir.y)
	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	
	// Convertir en coordonnées de la carte
	map_x = (int)new_x;
	map_y = (int)new_y;
	
	// Vérifier si la nouvelle position est un mur
	if (game->map[map_y][map_x] == '1')
	{
		// Si c'est un mur extérieur, ne pas autoriser le mouvement
		if (is_exterior_wall(game, map_x, map_y))
			return;
	}
	
	// Mettre à jour la position du joueur
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

/*
** Fait tourner le joueur et le plan de caméra
** param game: Pointeur vers la structure principale du jeu
** param angle: Angle de rotation en radians (positif pour droite, négatif pour gauche)
*/
void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// Sauvegarder l'ancienne direction X
	old_dir_x = game->player.dir.x;
	
	// Appliquer la matrice de rotation à la direction du joueur
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
	
	// Sauvegarder l'ancien plan de caméra X
	old_plane_x = game->player.plane.x;
	
	// Appliquer la même matrice de rotation au plan de caméra
	game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
}