/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:29:49 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/15 19:38:07 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	ft_printf("Touche pressée: %d\n", keycode);
	
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

int	key_release(int keycode, t_game *game)
{
	ft_printf("Touche relâchée: %d\n", keycode);
	
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

int	update_game(t_game *game)
{
	// Vérifier toutes les touches enfoncées et effectuer les actions correspondantes
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		move_left(game);
	if (game->keys[KEY_D])
		move_right(game);
	
	// Utiliser les variables spécifiques pour les flèches
	if (game->key_left)
		rotate(game, -ROT_SPEED);
	if (game->key_right)
		rotate(game, ROT_SPEED);
	
	// Rendre l'image
	return render(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (EXIT_FAILURE);
	}
	if (!is_valid_ext(argv[1], ".cub"))
	{
		ft_printf("Error\nInvalid file extension. Expected .cub\n");
		return (EXIT_FAILURE);
	}
	
	// Initialiser MLX avant de charger les textures
	if (!init_mlx(&game))
	{
		ft_printf("Error\nFailed to initialize MLX\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	
	if (!parse_file(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
		
	// Le reste de l'initialisation
	if (!init_player(&game))
	{
		ft_printf("Error\nFailed to initialize player\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	
	// Enregistrement des hooks
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);   // Appui sur une touche
	mlx_hook(game.win, 3, 1L << 1, key_release, &game); // Relâchement d'une touche
	mlx_hook(game.win, 17, 0, exit_hook, &game);       // Fermeture de la fenêtre
	mlx_loop_hook(game.mlx, update_game, &game);       // Utiliser update_game au lieu de render
	mlx_loop(game.mlx);
	
	return (EXIT_SUCCESS);
}