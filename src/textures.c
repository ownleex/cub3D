/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:34:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:27:17 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_tex_pixel(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	// Select texture based on the wall direction
	if (ray->side == 0) // X-side hit
	{
		if (ray->step.x < 0) // Ray is looking west (negative x)
			return (&game->tex.west);
		else // Ray is looking east (positive x)
			return (&game->tex.east);
	}
	else // Y-side hit
	{
		if (ray->step.y < 0) // Ray is looking north (negative y)
			return (&game->tex.north);
		else // Ray is looking south (positive y)
			return (&game->tex.south);
	}
}