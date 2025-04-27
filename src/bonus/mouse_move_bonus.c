/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:19:21 by cparodi           #+#    #+#             */
/*   Updated: 2025/04/27 16:19:23 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	sensi;

	(void)y;
	center_x = WINDOW_WIDTH / 2;
	delta_x = x - center_x;
	sensi = 0.003;
	if (game->mouse_captured)
	{
		mlx_mouse_hide(game->mlx, game->win);
		if (delta_x != 0)
		{
			rotate(game, delta_x * sensi);
			mlx_mouse_move(game->mlx, game->win, center_x, WINDOW_HEIGHT / 2);
		}
	}
	else
		mlx_mouse_show(game->mlx, game->win);
	return (0);
}
