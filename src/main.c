/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:29:49 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:27:08 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Point d'entrée du programme
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @return 0 si le programme s'exécute correctement, 1 sinon
 */
int	main(int argc, char **argv)
{
    t_game  game;

    // Vérifier les arguments
    if (argc != 2)
    {
        ft_printf("Error\nUsage: %s <map.cub>\n", argv[0]);
        return (1);
    }

    // Initialiser la structure du jeu
    if (!init_game(&game))
    {
        ft_printf("Error\nFailed to initialize game\n");
        return (1);
    }

    // Analyser le fichier de carte
    if (!parse_file(&game, argv[1]))
    {
        clean_exit(&game, 1);
    }

    // Configurer les hooks pour la gestion des événements
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);         // Touche enfoncée
    mlx_hook(game.win, 17, 0, exit_hook, &game);             // Croix de fermeture
    
    // Lancer la boucle principale
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);

    return (0);
}

/**
 * Fonction de hook pour la boucle principale
 * Cette fonction est appelée à chaque frame
 * @param game Pointeur vers la structure du jeu
 * @return 0 toujours
 */
int	render(t_game *game)
{
    // Vérifier que les structures nécessaires sont initialisées
    if (!game || !game->mlx || !game->win || !game->img.img)
        return (0);

    // Effectuer le raycasting pour calculer la scène 3D
    raycasting(game);
    
    // Afficher l'image à l'écran
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    
    return (0);
}