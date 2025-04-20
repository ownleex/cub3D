
#include "cub3d.h"

/* 
** Gère l'événement de pression d'une touche
** param keycode: Le code de la touche pressée
** param game: Pointeur vers la structure principale du jeu
** return: Toujours 0
*/
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, EXIT_SUCCESS);
	else if (keycode == KEY_W)
		game->keys[KEY_W] = 1;
	else if (keycode == KEY_A)
		game->keys[KEY_A] = 1;
	else if (keycode == KEY_S)
		game->keys[KEY_S] = 1;
	else if (keycode == KEY_D)
		game->keys[KEY_D] = 1;
	else if (keycode == KEY_LEFT)
		game->key_left = 1;
	else if (keycode == KEY_RIGHT)
		game->key_right = 1;
	return (0);
}

/* 
** Gère l'événement de relâchement d'une touche
** param keycode: Le code de la touche relâchée
** param game: Pointeur vers la structure principale du jeu
** return: Toujours 0
*/
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys[KEY_W] = 0;
	else if (keycode == KEY_A)
		game->keys[KEY_A] = 0;
	else if (keycode == KEY_S)
		game->keys[KEY_S] = 0;
	else if (keycode == KEY_D)
		game->keys[KEY_D] = 0;
	else if (keycode == KEY_LEFT)
		game->key_left = 0;
	else if (keycode == KEY_RIGHT)
		game->key_right = 0;
	return (0);
}

/* 
** Fonction appelée à chaque frame pour mettre à jour l'état du jeu
** Gère les mouvements du joueur en fonction des touches pressées
** param game: Pointeur vers la structure principale du jeu
** return: Résultat de la fonction render
*/
int	update_game(t_game *game)
{
	// Vérifie si des touches sont pressées
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		move_left(game);
	if (game->keys[KEY_D])
		move_right(game);
	if (game->key_left)
		rotate(game, -ROT_SPEED);
	if (game->key_right)
		rotate(game, ROT_SPEED);
	// Effectue le rendu de la frame actuelle
	return (render(game));
}

/* 
** Point d'entrée principal du programme
** param argc: Nombre d'arguments
** param argv: Tableau d'arguments
** return: Code de sortie du programme (SUCCESS ou FAILURE)
*/
int	main(int argc, char **argv)
{
	t_game	game;

	// Initialise la structure de jeu à zéro
	ft_memset(&game, 0, sizeof(t_game));
	
	// Vérifie que le programme a été lancé avec le bon nombre d'arguments
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (EXIT_FAILURE);
	}
	
	// Vérifie que le fichier fourni a bien l'extension .cub
	if (!is_valid_ext(argv[1], ".cub"))
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (EXIT_FAILURE);
	}
	
	// Initialise la bibliothèque MLX et crée la fenêtre
	if (!init_mlx(&game))
	{
		printf("Error\nFailed to initialize MLX\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	
	// Parse le fichier de carte
	if (!parse_file(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	
	// Initialise les données du joueur (position, direction)
	if (!init_player(&game))
	{
		printf("Error\nFailed to initialize player\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	
	// Configure les hooks pour les événements de clavier et de fermeture de fenêtre
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, exit_hook, &game);
	
	// Configure la fonction de mise à jour appelée à chaque frame
	mlx_loop_hook(game.mlx, update_game, &game);
	
	// Lance la boucle principale du jeu
	mlx_loop(game.mlx);
	
	return (EXIT_SUCCESS);
}