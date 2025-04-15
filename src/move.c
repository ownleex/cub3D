/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:34:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/15 21:36:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	
	// Calculate new position
	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	
	// Check for collision with walls
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	
	// Calculate new position
	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	
	// Check for collision with walls
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	
	// Calculate new position (moving perpendicular to the direction)
	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	
	// Check for collision with walls
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	
	// Calculate new position (moving perpendicular to the direction)
	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	
	// Check for collision with walls
	if (game->map[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	
	// Rotate direction vector
	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
	
	// Rotate camera plane
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
}