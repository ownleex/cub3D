/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:33:11 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/19 14:17:17 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_pos_dir(t_game *game, t_ray *ray, int x)
{
	// x-coordinate in camera space
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	
	// Which box of the map we're in
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	
	// Length of ray from one x or y-side to next x or y-side
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	// Calculate step and initial side_dist
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	// DDA algorithm
	while (!hit)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step.x;
			ray->side = 0; // X side hit
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step.y;
			ray->side = 1; // Y side hit
		}
		
		// Check if ray has hit a wall
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
	
	// Calculate distance projected on camera direction
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x + 
							(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y + 
							(1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_wall_height(t_ray *ray)
{
	// Sécuriser la distance projetée (évite les divisions par zéro ou les valeurs négatives)
	if (ray->perp_wall_dist < 0.000001)
		ray->perp_wall_dist = 0.000001;

	// Calculer la hauteur de la ligne à dessiner
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);

	// Déterminer le début de la ligne verticale à dessiner
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	//if (ray->draw_start >= WINDOW_HEIGHT)
	//	ray->draw_start = WINDOW_HEIGHT - 1;

	// Déterminer la fin de la ligne verticale à dessiner
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	//if (ray->draw_end < 0)
	//	ray->draw_end = 0;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}


void	calculate_texture_x(t_game *game, t_ray *ray)
{
	double	wall_x;
	
	// Calculate value of wall_x (where exactly the wall was hit)
	if (ray->side == 0)
		wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	ray->wall_x = wall_x;
	
	// x coordinate on the texture
	ray->tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	
	// Flip the texture if we hit the wall from the "inside"
	if ((ray->side == 0 && ray->dir.x > 0) || 
		(ray->side == 1 && ray->dir.y < 0))
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
}

void	raycasting(t_game *game)
{
	int	x;
	
	// For each column of the screen
	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		// Calculate ray position and direction
		calculate_ray_pos_dir(game, &game->ray, x);
		
		// Calculate step and initial side_dist
		calculate_step_and_side_dist(game, &game->ray);
		
		// Perform DDA
		perform_dda(game, &game->ray);
		
		// Calculate distance projected on camera direction
		calculate_wall_height(&game->ray);
		
		// Calculate texture coordinates
		calculate_texture_x(game, &game->ray);
		
		// Draw the column
		draw_vertical_line(game, x, &game->ray);
	}
}