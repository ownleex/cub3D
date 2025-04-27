/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:33:11 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/27 16:19:07 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_ray_pos_dir(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map_x) * \
ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - game->player.pos.x) * \
ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map_y) * \
ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - game->player.pos.y) * \
ray->delta_dist.y;
	}
}

void	calculate_wall_height(t_ray *ray)
{
	if (ray->perp_wall_dist < 0.000001)
		ray->perp_wall_dist = 0.000001;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

void	calculate_texture_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir.x > 0) || \
(ray->side == 1 && ray->dir.y < 0))
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray_pos_dir(game, &game->ray, x);
		calculate_step_and_side_dist(game, &game->ray);
		perform_dda(game, &game->ray);
		calculate_wall_height(&game->ray);
		calculate_texture_x(game, &game->ray);
		draw_vertical_line(game, x, &game->ray);
		x++;
	}
}
