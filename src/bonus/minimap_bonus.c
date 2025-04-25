/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:13:10 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/25 06:06:56 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_square(t_game *game, t_vector grid, int size, int color)
{
	int	i;
	int	j;
	int	pos_x;
	int	pos_y;

	pos_x = (int)grid.x * size + 10;
	pos_y = (int)grid.y * size + 10;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_img(game, pos_x + i, pos_y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_game *game, t_vector start, t_vector end, int color)
{
	t_vector	delta;
	int			nb_pixels;
	double		dir_x;
	double		dir_y;
	int			i;

	dir_x = end.x - start.x;
	dir_y = end.y - start.y;
	if (fabs(dir_x) > fabs(dir_y))
		nb_pixels = (int)fabs(dir_x);
	else
		nb_pixels = (int)fabs(dir_y);
	delta.x = dir_x / nb_pixels;
	delta.y = dir_y / nb_pixels;
	i = 0;
	while (i <= nb_pixels)
	{
		put_pixel_to_img(game, \
(int)(start.x + delta.x * i) + 10, \
(int)(start.y + delta.y * i) + 10, color);
		i++;
	}
}

void	draw_minimap_arrow(t_game *game, int size)
{
	t_vector	pos;
	t_vector	tip;
	t_vector	left;
	t_vector	right;

	pos.x = game->player.pos.x * size;
	pos.y = game->player.pos.y * size;
	tip.x = pos.x + game->player.dir.x * size * 0.8;
	tip.y = pos.y + game->player.dir.y * size * 0.8;
	left.x = pos.x - game->player.dir.y * size * 0.4;
	left.y = pos.y + game->player.dir.x * size * 0.4;
	right.x = pos.x + game->player.dir.y * size * 0.4;
	right.y = pos.y - game->player.dir.x * size * 0.4;
	draw_line(game, pos, tip, 0xFFFF00);
	draw_line(game, pos, left, 0xFFFF00);
	draw_line(game, pos, right, 0xFFFF00);
}

void	draw_minimap_background(t_game *game, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1')
				draw_minimap_square(game, (t_vector){j, i}, size, 0xFFFFFF);
			else if (game->map[i][j] == '0')
				draw_minimap_square(game, (t_vector){j, i}, size, 0x444444);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	max_dim;
	int	size;

	if (game->map_width > game->map_height)
		max_dim = game->map_width;
	else
		max_dim = game->map_height;
	size = 500 / max_dim;
	if (size < 2)
		size = 2;
	draw_minimap_background(game, size);
	draw_minimap_arrow(game, size);
}
