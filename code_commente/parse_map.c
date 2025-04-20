
#include "cub3d.h"

/*
** Trouve l'index de la première ligne de la carte dans le fichier
** param game: Pointeur vers la structure principale du jeu
** return: Index de la première ligne de la carte ou -1 si non trouvée
*/
int	find_map_start(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	// Ignorer les configurations de texture et de couleur
	while (game->file[i])
	{
		// Si la ligne commence par un identifiant connu ou est vide, l'ignorer
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 ||
			ft_strncmp(game->file[i], "SO ", 3) == 0 ||
			ft_strncmp(game->file[i], "WE ", 3) == 0 ||
			ft_strncmp(game->file[i], "EA ", 3) == 0 ||
			ft_strncmp(game->file[i], "F ", 2) == 0 ||
			ft_strncmp(game->file[i], "C ", 2) == 0 ||
			game->file[i][0] == '\0')
		{
			i++;
			continue;
		}
		// Vérifier si cette ligne contient des caractères de carte
		j = 0;
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' &&
				game->file[i][j] != 'N' && game->file[i][j] != 'S' &&
				game->file[i][j] != 'E' && game->file[i][j] != 'W' &&
				game->file[i][j] != ' ')
				break ;
			j++;
		}
		// Si tous les caractères sont valides, c'est le début de la carte
		if (game->file[i][j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

/*
** Compte le nombre de lignes de la carte à partir de la ligne de début
** param game: Pointeur vers la structure principale du jeu
** param start: Index de la première ligne de la carte
** return: Nombre de lignes de la carte
*/
int	count_map_height(t_game *game, int start)
{
	int	i;
	int	j;
	int	height;

	i = start;
	height = 0;
	while (game->file[i])
	{
		j = 0;
		// Vérifier si cette ligne fait toujours partie de la carte
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' &&
				game->file[i][j] != 'N' && game->file[i][j] != 'S' &&
				game->file[i][j] != 'E' && game->file[i][j] != 'W' &&
				game->file[i][j] != ' ')
				return (height);
			j++;
		}
		height++;
		i++;
	}
	return (height);
}

/*
** Détermine la largeur maximale de la carte
** param game: Pointeur vers la structure principale du jeu
** param start: Index de la première ligne de la carte
** param height: Nombre de lignes de la carte
** return: Largeur maximale de la carte
*/
int	get_map_width(t_game *game, int start, int height)
{
	int	i;
	int	max_width;
	int	line_width;

	max_width = 0;
	i = start; 
	while (i < start + height)
	{
		line_width = ft_strlen(game->file[i]);
		if (line_width > max_width)
			max_width = line_width;
		i++;
	}
	return (max_width);
}

/*
** Extrait la carte du fichier et crée un tableau 2D rectangulaire
** param game: Pointeur vers la structure principale du jeu
** param start: Index de la première ligne de la carte
** param height: Nombre de lignes de la carte
** param width: Largeur maximale de la carte
** return: true si l'extraction a réussi, false sinon
*/
bool	extract_map(t_game *game, int start, int height, int width)
{
	int	i;
	int	j;

	// Allouer de la mémoire pour le tableau 2D
	game->map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (false);
	
	i = 0; 
	while (i < height)
	{
		// Allouer de la mémoire pour chaque ligne
		game->map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!game->map[i])
			return (false);
		
		// Copier la ligne et compléter avec des espaces
		j = 0; 
		while (j < width)
		{
			if (j < (int)ft_strlen(game->file[start + i]))
				game->map[i][j] = game->file[start + i][j];
			else
				game->map[i][j] = ' ';
			j++;
		}
		game->map[i][width] = '\0';
		i++;
	}
	// Terminer le tableau par NULL
	game->map[height] = NULL;
	return (true);
}

/*
** Configure la position et la direction initiale du joueur
** param game: Pointeur vers la structure principale du jeu
** param x: Position x du joueur sur la carte
** param y: Position y du joueur sur la carte
** param dir: Caractère indiquant la direction (N, S, E, W)
** return: true si la configuration a réussi
*/
bool	set_player_position(t_game *game, int x, int y, char dir)
{
	// Configurer la position du joueur au centre de la case
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	
	// Configurer la direction et le plan de caméra selon l'orientation indiquée
	if (dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	// Remplacer le caractère du joueur par un sol dans la carte
	game->map[y][x] = '0';
	return (true);
}

/*
** Recherche la position du joueur dans la carte et configure ses propriétés
** param game: Pointeur vers la structure principale du jeu
** return: true si exactement une position de joueur a été trouvée
*/
bool	find_player(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0; 
	while (y < game->map_height)
	{
		x = 0; 
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (false); // Plus d'une position de joueur trouvée
				set_player_position(game, x, y, game->map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

/*
** Vérifie que les bordures de la carte sont correctement fermées par des murs
** param game: Pointeur vers la structure principale du jeu
** return: true si les bordures sont correctement fermées
*/
bool	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	// Vérifier les bordures horizontales
	y = 0; 
	while (y < game->map_height)
	{
		// Trouver le premier caractère non-espace depuis la gauche
		x = 0;
		while (x < game->map_width && game->map[y][x] == ' ')
			x++;
		if (x < game->map_width && game->map[y][x] != '1')
			return (false);
		
		// Trouver le premier caractère non-espace depuis la droite
		x = game->map_width - 1;
		while (x >= 0 && game->map[y][x] == ' ')
			x--;
		if (x >= 0 && game->map[y][x] != '1')
			return (false);
		y++;
	}
	
	// Vérifier les bordures verticales
	x = 0; 
	while (x < game->map_width)
	{
		// Trouver le premier caractère non-espace depuis le haut
		y = 0;
		while (y < game->map_height && game->map[y][x] == ' ')
			y++;
		if (y < game->map_height && game->map[y][x] != '1')
			return (false);
		
		// Trouver le premier caractère non-espace depuis le bas
		y = game->map_height - 1;
		while (y >= 0 && game->map[y][x] == ' ')
			y--;
		if (y >= 0 && game->map[y][x] != '1')
			return (false);
		x++;
	}
	
	return (true);
}

/*
** Vérifie que la carte est complètement fermée par des murs
** param game: Pointeur vers la structure principale du jeu
** return: true si la carte est correctement fermée
*/
bool	check_map_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0; 
	while (y < game->map_height)
	{
		x = 0; 
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
			{
				// Vérifier si la case est sur une bordure de la carte
				if (y == 0 || y == game->map_height - 1 || 
					x == 0 || x == game->map_width - 1)
					return (false);
				
				// Vérifier les cases adjacentes
				if (game->map[y-1][x] == ' ' || game->map[y+1][x] == ' ' ||
					game->map[y][x-1] == ' ' || game->map[y][x+1] == ' ')
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

/*
** Vérifie que la carte ne contient que des caractères valides
** param game: Pointeur vers la structure principale du jeu
** return: true si tous les caractères sont valides
*/
bool	check_map_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0; 
	while (y < game->map_height)
	{
		x = 0; 
		while (x < game->map_width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' &&
				game->map[y][x] != 'N' && game->map[y][x] != 'S' &&
				game->map[y][x] != 'E' && game->map[y][x] != 'W' &&
				game->map[y][x] != ' ')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

/*
** Vérifie la validité globale de la carte
** param game: Pointeur vers la structure principale du jeu
** return: true si la carte est valide
*/
bool	validate_map(t_game *game)
{
	// Vérifier que tous les caractères sont valides
	if (!check_map_chars(game))
	{
		ft_printf("Error\nInvalid characters in map\n");
		return (false);
	}
	// Vérifier qu'il y a exactement une position de joueur
	if (!find_player(game))
	{
		ft_printf("Error\nMap must contain exactly one player position (N, S, E, or W)\n");
		return (false);
	}
	// Vérifier que les bordures sont des murs
	if (!check_map_borders(game))
	{
		ft_printf("Error\nMap borders must be walls (1) or surrounded by walls\n");
		return (false);
	}
	// Vérifier que la carte est complètement fermée
	if (!check_map_closed(game))
	{
		ft_printf("Error\nMap must be completely enclosed by walls\n");
		return (false);
	}
	return (true);
}

/*
** Fonction principale d'analyse de la carte
** param game: Pointeur vers la structure principale du jeu
** return: true si l'analyse a réussi
*/
bool	parse_map(t_game *game)
{
	int	start;
	int	height;
	int	width;

	// Trouver la première ligne de la carte
	start = find_map_start(game);
	if (start < 0)
	{
		ft_printf("Error\nCould not find map in file\n");
		return (false);
	}
	
	// Déterminer la hauteur de la carte
	height = count_map_height(game, start);
	if (height <= 0)
	{
		ft_printf("Error\nInvalid map height\n");
		return (false);
	}
	
	// Déterminer la largeur de la carte
	width = get_map_width(game, start, height);
	if (width <= 0)
	{
		ft_printf("Error\nInvalid map width\n");
		return (false);
	}
	
	// Extraire la carte du fichier
	if (!extract_map(game, start, height, width))
	{
		ft_printf("Error\nFailed to extract map\n");
		return (false);
	}
	
	// Stocker les dimensions de la carte
	game->map_height = height;
	game->map_width = width;
	
	// Valider la carte
	return (validate_map(game));
}