/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/15 19:06:22 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_texture(t_game *game, t_texture *texture, char *path)
{
	// Supprimer les espaces possibles au début
	while (*path && (*path == ' ' || *path == '\t'))
		path++;

	// Charger la texture à partir du fichier XPM
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_printf("Error\nImpossible de charger la texture: %s\n", path);
		return (false);
	}
	
	// Obtenir l'adresse de l'image
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	
	// Vérifier que la texture est exactement de 64x64 pixels
	if (texture->width != 64 || texture->height != 64)
	{
		ft_printf("Error\nLa texture %s n'est pas de 64x64 pixels (dimensions actuelles: %dx%d)\n", 
			path, texture->width, texture->height);
		// Libérer la texture déjà chargée
		mlx_destroy_image(game->mlx, texture->img);
		texture->img = NULL;
		return (false);
	}
	
	return (true);
}

bool	parse_color_value(char *str, int *rgb)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	
	while (str[i])
	{
		// Ignorer les espaces
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		
		// Analyser la composante RGB
		if (ft_isdigit(str[i]))
		{
			if (count >= 3)
				return (false); // Trop de composantes
			
			rgb[count] = ft_atoi(&str[i]);
			if (rgb[count] < 0 || rgb[count] > 255)
				return (false); // Valeur de composante invalide
			
			count++;
			
			// Ignorer les chiffres
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		
		// Ignorer la virgule ou l'espace
		if (str[i] == ',')
			i++;
		else if (str[i] && str[i] != ' ' && str[i] != '\t')
			return (false); // Caractère invalide
	}
	
	return (count == 3); // Doit avoir exactement 3 composantes
}

bool	parse_color(t_game *game, char *line, char type)
{
	int		rgb[3];
	int		color;
	char	*value;
	
	// Ignorer l'identifiant et les espaces
	value = line + 1;
	while (*value && (*value == ' ' || *value == '\t'))
		value++;
	
	if (!parse_color_value(value, rgb))
	{
		ft_printf("Error\nFormat de couleur invalide: %s\n", line);
		return (false);
	}
	
	color = create_rgb(rgb[0], rgb[1], rgb[2]);
	
	if (type == 'F')
		game->tex.floor = color;
	else
		game->tex.ceiling = color;
	
	return (true);
}

bool	parse_texture_line(t_game *game, char *line)
{
	// Analyser les chemins de texture en fonction de l'identifiant
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (load_texture(game, &game->tex.north, line + 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (load_texture(game, &game->tex.south, line + 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (load_texture(game, &game->tex.west, line + 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (load_texture(game, &game->tex.east, line + 3));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(game, line, 'F'));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(game, line, 'C'));
	
	// Ignorer les lignes vides et autre contenu (la carte sera analysée séparément)
	return (true);
}

bool	check_textures_loaded(t_game *game)
{
	// Vérifier que toutes les textures et couleurs requises sont chargées
	if (!game->tex.north.img || !game->tex.south.img ||
		!game->tex.east.img || !game->tex.west.img)
		return (false);
	
	// Les couleurs utilisent 0 comme valeur par défaut, donc nous ne pouvons pas les vérifier directement
	// Au lieu de cela, nous comptons sur le processus d'analyse pour s'assurer qu'elles sont définies.
	
	return (true);
}

bool	parse_textures(t_game *game)
{
	int	i;
	
	i = 0;
	while (game->file[i])
	{
		// Ignorer les lignes vides
		if (game->file[i][0] == '\0')
		{
			i++;
			continue;
		}
		
		// Traiter les lignes de texture et de couleur
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 ||
			ft_strncmp(game->file[i], "SO ", 3) == 0 ||
			ft_strncmp(game->file[i], "WE ", 3) == 0 ||
			ft_strncmp(game->file[i], "EA ", 3) == 0 ||
			ft_strncmp(game->file[i], "F ", 2) == 0 ||
			ft_strncmp(game->file[i], "C ", 2) == 0)
		{
			if (!parse_texture_line(game, game->file[i]))
				return (false);
		}
		
		i++;
	}
	
	return (check_textures_loaded(game));
}