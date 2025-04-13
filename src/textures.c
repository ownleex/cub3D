/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:34:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:19:01 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Récupère la couleur d'un pixel d'une texture
 * @param img Pointeur vers la structure d'image
 * @param x Coordonnée x dans la texture
 * @param y Coordonnée y dans la texture
 * @return La couleur du pixel
 */
int	get_tex_pixel(t_img *img, int x, int y)
{
    char    *dst;
    int     color;

    // Vérifier que l'image est valide
    if (!img || !img->addr)
        return (0);
    
    // Vérifier que les coordonnées sont dans les limites
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    
    // Calculer l'adresse du pixel
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    
    // Récupérer la couleur
    color = *(unsigned int*)dst;
    
    return (color);
}

/**
 * Sélectionne la texture appropriée en fonction de la direction du rayon
 * @param game Pointeur vers la structure du jeu
 * @param ray Pointeur vers la structure du rayon
 * @return Pointeur vers la texture appropriée
 */
t_img	*select_texture(t_game *game, t_ray *ray)
{
    // Vérifier que les pointeurs sont valides
    if (!game || !ray)
        return (NULL);
    
    // Sélectionner la texture selon le côté touché
    if (ray->side == 0)
    {
        // Mur horizontal
        if (ray->step.x > 0)
            return (&game->tex.east);  // Face est
        else
            return (&game->tex.west);  // Face ouest
    }
    else
    {
        // Mur vertical
        if (ray->step.y > 0)
            return (&game->tex.south); // Face sud
        else
            return (&game->tex.north); // Face nord
    }
}