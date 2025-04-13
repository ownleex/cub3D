/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:18:33 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Analyse et charge les textures depuis le fichier de configuration
 * @param game Pointeur vers la structure du jeu
 * @return true si l'analyse réussit, false sinon
 */
bool	parse_textures(t_game *game)
{
    int    i;
    char    **split;
    char    *line;
    bool    north_set;
    bool    south_set;
    bool    east_set;
    bool    west_set;
    bool    floor_set;
    bool    ceiling_set;

    i = 0;
    north_set = false;
    south_set = false;
    east_set = false;
    west_set = false;
    floor_set = false;
    ceiling_set = false;

    // Vérifier que le fichier a été chargé
    if (!game->file)
    {
        ft_printf("Error\nFile content not loaded\n");
        return (false);
    }

    // S'assurer que MLX est initialisé avant de charger les textures
    if (!game->mlx)
    {
        ft_printf("Error\nMLX not initialized before loading textures\n");
        return (false);
    }

    // Parcourir les lignes du fichier
    while (game->file[i])
    {
        line = game->file[i];
        
        // Ignorer les lignes vides
        if (line[0] == '\0')
        {
            i++;
            continue;
        }
        
        // Séparer l'identifiant et le chemin/valeur
        split = ft_split(line, ' ');
        if (!split)
        {
            ft_printf("Error\nMemory allocation failed during texture parsing\n");
            return (false);
        }

        // Vérifier que nous avons au moins deux éléments (identifiant et valeur)
        if (!split[0] || !split[1])
        {
            ft_printf("Error\nInvalid texture format: %s\n", line);
            free_split(split);
            return (false);
        }

        // Traiter selon l'identifiant
        if (ft_strncmp(split[0], "NO", 3) == 0 && !north_set)
        {
            if (!load_texture(game, &game->tex.north, split[1]))
            {
                free_split(split);
                return (false);
            }
            north_set = true;
        }
        else if (ft_strncmp(split[0], "SO", 3) == 0 && !south_set)
        {
            if (!load_texture(game, &game->tex.south, split[1]))
            {
                free_split(split);
                return (false);
            }
            south_set = true;
        }
        else if (ft_strncmp(split[0], "WE", 3) == 0 && !west_set)
        {
            if (!load_texture(game, &game->tex.west, split[1]))
            {
                free_split(split);
                return (false);
            }
            west_set = true;
        }
        else if (ft_strncmp(split[0], "EA", 3) == 0 && !east_set)
        {
            if (!load_texture(game, &game->tex.east, split[1]))
            {
                free_split(split);
                return (false);
            }
            east_set = true;
        }
        else if (ft_strncmp(split[0], "F", 2) == 0 && !floor_set)
        {
            if (!parse_color(game, split[1], 'F'))
            {
                free_split(split);
                return (false);
            }
            floor_set = true;
        }
        else if (ft_strncmp(split[0], "C", 2) == 0 && !ceiling_set)
        {
            if (!parse_color(game, split[1], 'C'))
            {
                free_split(split);
                return (false);
            }
            ceiling_set = true;
        }

        free_split(split);
        
        // Si toutes les textures et couleurs sont définies, nous pouvons arrêter
        if (north_set && south_set && east_set && west_set && floor_set && ceiling_set)
            break;
        
        i++;
    }

    // Vérifier que toutes les textures et couleurs nécessaires ont été définies
    if (!north_set || !south_set || !east_set || !west_set || !floor_set || !ceiling_set)
    {
        ft_printf("Error\nMissing texture information\n");
        return (false);
    }

    return (true);
}

/**
 * Charge une texture depuis un fichier XPM
 * @param game Pointeur vers la structure du jeu
 * @param img Pointeur vers la structure d'image à initialiser
 * @param path Chemin vers le fichier de texture
 * @return true si le chargement réussit, false sinon
 */
bool	load_texture(t_game *game, t_img *img, char *path)
{
    // Vérifier que les pointeurs ne sont pas NULL
    if (!game || !img || !path)
    {
        ft_printf("Error\nInvalid parameters for loading texture\n");
        return (false);
    }

    // Vérifier que MLX est initialisé
    if (!game->mlx)
    {
        ft_printf("Error\nMLX not initialized before loading texture\n");
        return (false);
    }

    // Vérifier que le chemin est valide
    if (access(path, F_OK) != 0)
    {
        ft_printf("Error\nCould not access texture file: %s\n", path);
        return (false);
    }

    // Charger l'image XPM
    img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
    if (!img->img)
    {
        ft_printf("Error\nCould not load texture: %s\n", path);
        return (false);
    }

    // Obtenir les informations de l'image
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, 
                                  &img->line_length, &img->endian);
    if (!img->addr)
    {
        ft_printf("Error\nCould not get image data for: %s\n", path);
        mlx_destroy_image(game->mlx, img->img);
        img->img = NULL;
        return (false);
    }

    return (true);
}

/**
 * Analyse une chaîne de caractères représentant une couleur RGB
 * @param game Pointeur vers la structure du jeu
 * @param line Chaîne contenant les valeurs R,G,B
 * @param type Type de couleur ('F' pour sol, 'C' pour plafond)
 * @return true si l'analyse réussit, false sinon
 */
bool	parse_color(t_game *game, char *line, char type)
{
    char    **split;
    int     r;
    int     g;
    int     b;

    // Vérifier que la ligne n'est pas vide
    if (!line || line[0] == '\0')
    {
        ft_printf("Error\nEmpty color value\n");
        return (false);
    }

    // Séparer les composantes R,G,B
    split = ft_split(line, ',');
    if (!split || !split[0] || !split[1] || !split[2] || split[3])
    {
        ft_printf("Error\nInvalid color format: %s\n", line);
        if (split)
            free_split(split);
        return (false);
    }

    // Convertir les chaînes en entiers
    r = ft_atoi(split[0]);
    g = ft_atoi(split[1]);
    b = ft_atoi(split[2]);

    // Vérifier que les valeurs sont dans la plage [0-255]
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        ft_printf("Error\nColor values must be between 0 and 255\n");
        free_split(split);
        return (false);
    }

    // Stocker la couleur dans la structure appropriée
    if (type == 'F')
        game->tex.floor = create_rgb(r, g, b);
    else if (type == 'C')
        game->tex.ceiling = create_rgb(r, g, b);

    free_split(split);
    return (true);
}