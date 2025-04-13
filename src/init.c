/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:18:14 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Initialise la structure du jeu
 * @param game Pointeur vers la structure du jeu
 * @return true si l'initialisation réussit, false sinon
 */
bool	init_game(t_game *game)
{
    // Initialiser tous les champs à 0 ou NULL
    ft_bzero(game, sizeof(t_game));
    
    // Initialiser le moteur MLX
    if (!init_mlx(game))
        return (false);
    
    // Définir que les textures ne sont pas chargées
    game->textures_loaded = false;
    
    return (true);
}

/**
 * Initialise la bibliothèque MLX
 * @param game Pointeur vers la structure du jeu
 * @return true si l'initialisation réussit, false sinon
 */
bool	init_mlx(t_game *game)
{
    // Initialiser la connexion MLX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_printf("Error\nFailed to initialize MLX\n");
        return (false);
    }
    
    // Créer la fenêtre
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!game->win)
    {
        ft_printf("Error\nFailed to create window\n");
        return (false);
    }
    
    // Créer une image pour le rendu
    game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img.img)
    {
        ft_printf("Error\nFailed to create image\n");
        return (false);
    }
    
    // Obtenir les informations de l'image
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
            &game->img.line_length, &game->img.endian);
    
    // Initialiser la taille de l'image
    game->img.width = WINDOW_WIDTH;
    game->img.height = WINDOW_HEIGHT;
    
    return (true);
}

/**
 * Initialise les textures du jeu
 * @param game Pointeur vers la structure du jeu
 * @return true si l'initialisation réussit, false sinon
 */
bool	init_texture(t_game *game)
{
    // Vérifier que MLX est initialisé
    if (!game->mlx)
    {
        ft_printf("Error\nMLX not initialized before loading textures\n");
        return (false);
    }
    
    // Si les textures ont déjà été chargées, ne pas les recharger
    if (game->textures_loaded)
        return (true);
    
    // Créer une image provisoire pour vérifier que MLX fonctionne correctement
    void *test_img = mlx_new_image(game->mlx, 1, 1);
    if (!test_img)
    {
        ft_printf("Error\nFailed to create test image\n");
        return (false);
    }
    mlx_destroy_image(game->mlx, test_img);
    
    // Marquer les textures comme chargées
    game->textures_loaded = true;
    
    return (true);
}