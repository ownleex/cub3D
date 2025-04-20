
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

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

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01

/* Structure pour représenter un vecteur 2D avec des coordonnées en virgule flottante */
typedef struct s_vector {
	double	x;              /* Composante x du vecteur */
	double	y;              /* Composante y du vecteur */
}	t_vector;

/* Structure pour gérer une texture */
typedef struct s_texture {
	void	*img;           /* Pointeur vers l'image MLX */
	char	*addr;          /* Adresse des données de l'image */
	int		bits_per_pixel; /* Nombre de bits par pixel */
	int		line_length;    /* Longueur d'une ligne en octets */
	int		endian;         /* Endianness de l'image */
	int		width;          /* Largeur de la texture en pixels */
	int		height;         /* Hauteur de la texture en pixels */
}	t_texture;

/* Structure regroupant toutes les textures du jeu */
typedef struct s_tex {
	t_texture	north;      /* Texture du mur orienté vers le nord */
	t_texture	south;      /* Texture du mur orienté vers le sud */
	t_texture	east;       /* Texture du mur orienté vers l'est */
	t_texture	west;       /* Texture du mur orienté vers l'ouest */
	int		floor;          /* Couleur RGB du sol */
	int		ceiling;        /* Couleur RGB du plafond */
}	t_tex;

/* Structure contenant les informations d'un rayon lors du raycasting */
typedef struct s_ray {
	t_vector	dir;        /* Direction du rayon */
	t_vector	delta_dist; /* Distance entre les intersections avec les lignes x ou y */
	t_vector	side_dist;  /* Distance jusqu'à la prochaine intersection avec une ligne x ou y depuis la position actuelle */
	t_vector	step;       /* Direction de pas (1 ou -1) pour x et y lors du DDA */
	int			map_x;      /* Position x dans la grille de la carte */
	int			map_y;      /* Position y dans la grille de la carte */
	int			side;       /* Indique si un mur a été touché côté x (0) ou côté y (1) */
	double		perp_wall_dist; /* Distance perpendiculaire du joueur au mur touché */
	double		wall_x;     /* Coordonnée exacte où le rayon a touché le mur (pour le texturing) */
	int			tex_x;      /* Coordonnée x de la texture à appliquer */
	int			line_height; /* Hauteur de la ligne verticale à dessiner */
	int			draw_start; /* Pixel de début de dessin de la ligne (y) */
	int			draw_end;   /* Pixel de fin de dessin de la ligne (y) */
}	t_ray;

/* Structure représentant le joueur */
typedef struct s_player {
	t_vector	pos;        /* Position du joueur sur la carte */
	t_vector	dir;        /* Direction dans laquelle regarde le joueur */
	t_vector	plane;      /* Plan de la caméra (perpendiculaire à la direction) */
}	t_player;

/* Structure principale du jeu contenant toutes les informations */
typedef struct s_game {
	void		*mlx;       /* Pointeur pour la MLX */
	void		*win;       /* Pointeur vers la fenêtre MLX */
	void		*img;       /* Pointeur vers l'image principale */
	char		*img_addr;  /* Adresse des données de l'image principale */
	int			img_bits_per_pixel; /* Bits par pixel de l'image principale */
	int			img_line_length;    /* Taille d'une ligne en octets */
	int			img_endian;         /* Endianness de l'image */
	t_tex		tex;        /* Toutes les textures du jeu */
	t_player	player;     /* Informations sur le joueur */
	t_ray		ray;        /* Informations sur le rayon actuel lors du raycasting */
	char		**map;      /* Carte du jeu sous forme de tableau 2D */
	char		**file;     /* Contenu du fichier .cub */
	int			map_width;  /* Largeur de la carte */
	int			map_height; /* Hauteur de la carte */
	bool		textures_loaded; /* Indique si les textures ont été chargées avec succès */
	int			keys[128];  /* Tableau pour suivre l'état des touches standard */
	int			key_left;   /* État de la flèche gauche */
	int			key_right;  /* État de la flèche droite */
}	t_game;

/* init.c */
bool	init_mlx(t_game *game);
bool	init_texture_data(t_game *game);
bool	create_texture(t_game *game, t_texture *texture, int width, int height);
bool	init_player(t_game *game);

/* parse.c */
bool	parse_file(t_game *game, char *file_path);
int		open_file(char *file_path);
bool	load_file_content(t_game *game, int fd);

/* parse_map.c */
bool	parse_map(t_game *game);
bool	validate_map(t_game *game);
bool	check_map_chars(t_game *game);
bool	check_map_borders(t_game *game);
bool	set_player_position(t_game *game, int x, int y, char dir);

/* parse_texture.c */
bool	parse_textures(t_game *game);
bool	load_texture(t_game *game, t_texture *texture, char *path);
bool	parse_color(t_game *game, char *line, char type);

/* raycasting.c */
void	raycasting(t_game *game);
void	calculate_ray_pos_dir(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);

/* render.c */
int		render(t_game *game);
void	draw_vertical_line(t_game *game, int x, t_ray *ray);
void	put_pixel_to_img(t_game *game, int x, int y, int color);

/* textures.c */
int		get_tex_pixel(t_texture *texture, int x, int y);
t_texture	*select_texture(t_game *game, t_ray *ray);

/* move.c */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate(t_game *game, double angle);

/* utils.c */
bool	is_valid_ext(char *file, char *ext);
int		create_rgb(int r, int g, int b);

/* exit.c */
void	clean_exit(t_game *game, int status);
int		exit_hook(t_game *game);
void	free_textures(t_game *game);
void	error_exit(t_game *game, char *message);

/* hooks.c */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		update_game(t_game *game);

#endif