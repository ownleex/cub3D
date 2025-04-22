/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:30:45 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/23 00:24:13 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define MOVE_SPEED 0.025
# define ROT_SPEED 0.02

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_tex
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	int			floor;
	int			ceiling;
}	t_tex;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	step;
	int			map_x;
	int			map_y;
	int			side;
	double		perp_wall_dist;
	int			tex_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			img_bits_per_pixel;
	int			img_line_length;
	int			img_endian;
	t_tex		tex;
	t_player	player;
	t_ray		ray;
	char		**map;
	char		**file;
	int			map_width;
	int			map_height;
	int			keys[128];
	int			key_left;
	int			key_right;
}	t_game;

/* init.c */
bool		init_mlx(t_game *game);
bool		init_player(t_game *game);

/* parse.c */
bool		parse_file(t_game *game, char *file_path);
int			open_file(char *file_path);
bool		load_file_content(t_game *game, int fd);
t_game		parsing(t_game game, char *argv);

/* parse_map_1.c */
bool		get_map_params(t_game *game, int *start, int *height, int *width);
bool		parse_map(t_game *game);

/*parse_map_2.c */
int			find_map_start(t_game *game);
int			count_map_height(t_game *game, int start);
int			get_map_width(t_game *game, int start, int height);
bool		extract_map(t_game *game, int start, int height, int width);

/*parse_map_3.c */
bool		check_map_chars(t_game *game);
bool		check_row_borders(t_game *game);
bool		check_col_borders(t_game *game);
bool		check_map_closed(t_game *game);
bool		validate_map(t_game *game);

/*parse_map_4.c */
void		set_ns_direction(t_player *player, char dir);
void		set_ew_direction(t_player *player, char dir);
bool		set_player_position(t_game *game, int x, int y, char dir);
bool		find_player(t_game *game);
bool		check_map_borders(t_game *game);

/* parse_texture.c */
bool		parse_textures(t_game *game);
bool		load_texture(t_game *game, t_texture *texture, char *path);
bool		parse_color(t_game *game, char *line, char type);

/* raycasting.c */
void		raycasting(t_game *game);
void		calculate_ray_pos_dir(t_game *game, t_ray *ray, int x);

/* render.c */
int			render(t_game *game);
void		draw_vertical_line(t_game *game, int x, t_ray *ray);
void		put_pixel_to_img(t_game *game, int x, int y, int color);

/* textures.c */
int			get_tex_pixel(t_texture *texture, int x, int y);
t_texture	*select_texture(t_game *game, t_ray *ray);

/* move.c */
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate(t_game *game, double angle);

/* utils.c */
bool		is_valid_ext(char *file, char *ext);
int			create_rgb(int r, int g, int b);

/* exit.c */
void		clean_exit(t_game *game, int status);
int			exit_hook(t_game *game);
void		free_textures(t_game *game);

/* hooks in main.c */
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			update_game(t_game *game);

/* wall.c */
bool		is_exterior_wall(t_game *game, int x, int y);

/* free.c */
void		free_file(t_game *game);

/* dda.c */
void		perform_dda(t_game *game, t_ray *ray);

#endif