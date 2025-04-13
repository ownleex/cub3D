/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:33:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/13 23:40:32 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return;
	dst = game->img_addr + (y * game->img_line_length + x * (game->img_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_ceiling_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	// Draw ceiling
	for (y = 0; y < ray->draw_start; y++)
		put_pixel_to_img(game, x, y, game->tex.ceiling);
	
	// Draw floor
	for (y = ray->draw_end + 1; y < WINDOW_HEIGHT; y++)
		put_pixel_to_img(game, x, y, game->tex.floor);
}

void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	tex = select_texture(game, ray);
	
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	
	// Starting texture coordinate
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	
	// Draw the wall from draw_start to draw_end
	for (y = ray->draw_start; y <= ray->draw_end; y++)
	{
		// Cast the texture coordinate to integer
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		
		// Get the color from the texture
		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		
		// Put pixel to image
		put_pixel_to_img(game, x, y, color);
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray *ray)
{
	// Draw ceiling and floor
	draw_ceiling_floor(game, x, ray);
	
	// Draw textured wall
	draw_textured_wall(game, x, ray);
}

int	render(t_game *game)
{
	// Clear the image
	ft_memset(game->img_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 
			(game->img_bits_per_pixel / 8));
	
	// Perform raycasting
	raycasting(game);
	
	// Put the image to the window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	
	return (0);
}