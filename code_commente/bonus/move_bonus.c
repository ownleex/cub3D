
#include "cub3d.h"

/*
** Déplace le joueur vers l'avant avec gestion des collisions
** Cette fonction vérifie si le mouvement est possible avant de l'effectuer
** param game: Pointeur vers la structure principale du jeu
*/
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	// Calculer les nouvelles coordonnées potentielles
	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	
	// Vérifier si la nouvelle position en X est valide (n'est pas un mur)
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	
	// Vérifier si la nouvelle position en Y est valide (n'est pas un mur)
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers l'arrière avec gestion des collisions
** Cette fonction vérifie si le mouvement est possible avant de l'effectuer
** param game: Pointeur vers la structure principale du jeu
*/
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	// Calculer les nouvelles coordonnées potentielles (direction inverse)
	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	
	// Vérifier si la nouvelle position en X est valide (n'est pas un mur)
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	
	// Vérifier si la nouvelle position en Y est valide (n'est pas un mur)
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers la gauche avec gestion des collisions
** Le déplacement est perpendiculaire à la direction du regard
** param game: Pointeur vers la structure principale du jeu
*/
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	// Calculer les nouvelles coordonnées potentielles
	// Pour aller à gauche, on utilise (dir.y, -dir.x) qui est perpendiculaire à (dir.x, dir.y)
	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	
	// Vérifier si la nouvelle position en X est valide (n'est pas un mur)
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	
	// Vérifier si la nouvelle position en Y est valide (n'est pas un mur)
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

/*
** Déplace le joueur vers la droite avec gestion des collisions
** Le déplacement est perpendiculaire à la direction du regard
** param game: Pointeur vers la structure principale du jeu
*/
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	// Calculer les nouvelles coordonnées potentielles
	// Pour aller à droite, on utilise (-dir.y, dir.x) qui est perpendiculaire à (dir.x, dir.y)
	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	
	// Vérifier si la nouvelle position en X est valide (n'est pas un mur)
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	
	// Vérifier si la nouvelle position en Y est valide (n'est pas un mur)
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

/*
** Fait tourner le joueur et le plan de caméra
** Cette fonction applique une matrice de rotation 2D
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
	// [cos(angle) -sin(angle)] [dir.x]
	// [sin(angle)  cos(angle)] [dir.y]
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
	
	// Sauvegarder l'ancien plan de caméra X
	old_plane_x = game->player.plane.x;
	
	// Appliquer la même matrice de rotation au plan de caméra
	// pour que celui-ci reste perpendiculaire à la direction
	game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
}