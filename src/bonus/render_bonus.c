/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:33:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/23 15:22:12 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	dst = game->img_addr + (y * game->img_line_length + x * \
(game->img_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceiling_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(game, x, y, game->tex.ceiling);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel_to_img(game, x, y, game->tex.floor);
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, t_ray *ray, int y)
{
	t_texture	*tex;
	int			tex_y;
	int			color;
	double		step;
	double		tex_pos;

	if (game->map[ray->map_y][ray->map_x] == 'D')
	{
		tex = &game->tex.door;
	}
	else
	{
		tex = select_texture(game, ray);
	}
	step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + \
ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		put_pixel_to_img(game, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray *ray)
{
	draw_ceiling_floor(game, x, ray);
	draw_textured_wall(game, x, ray, 0);
}

int	render(t_game *game)
{
	ft_memset(game->img_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * \
(game->img_bits_per_pixel / 8));
	raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
