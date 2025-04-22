/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:35:02 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/22 23:58:32 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	hit_check(t_game *game, t_ray *ray)
{
	if (game->map[ray->map_y][ray->map_x] == '1')
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side = 0;
			ray->perp_wall_dist = ray->side_dist.x;
		}
		else
		{
			ray->side = 1;
			ray->perp_wall_dist = ray->side_dist.y;
		}
		return (true);
	}
	return (false);
}

static void	run_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step.y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
}

static void	wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	if (hit_check(game, ray))
		return ;
	run_dda(game, ray);
	wall_distance(game, ray);
}
