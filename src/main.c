/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:29:49 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:35:23 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, EXIT_SUCCESS);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate(game, ROT_SPEED);
	return (0);
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
	
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, exit_hook, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	
	return (EXIT_SUCCESS);
}