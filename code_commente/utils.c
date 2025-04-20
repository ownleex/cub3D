
#include "cub3d.h"

/*
** Vérifie si le fichier a l'extension spécifiée
** param file: Nom du fichier à vérifier
** param ext: Extension à vérifier (avec le point, par exemple ".cub")
** return: true si le fichier a l'extension spécifiée, false sinon
*/
bool	is_valid_ext(char *file, char *ext)
{
	int	file_len;
	int	ext_len;

	// Vérifier que les paramètres ne sont pas NULL
	if (!file || !ext)
		return (false);
	
	// Obtenir les longueurs des chaînes
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	
	// Vérifier que le nom de fichier est plus long que l'extension
	if (file_len <= ext_len)
		return (false);
	
	// Comparer la fin du nom de fichier avec l'extension
	return (ft_strncmp(file + file_len - ext_len, ext, ext_len + 1) == 0);
}

/*
** Crée une couleur RGB à partir de ses composantes
** param r: Composante rouge (0-255)
** param g: Composante verte (0-255)
** param b: Composante bleue (0-255)
** return: Valeur de couleur RGB encodée en int
*/
int	create_rgb(int r, int g, int b)
{
	// Combiner les composantes RGB en une seule valeur
	// Format: 0xRRGGBB (hexadécimal)
	return ((r << 16) | (g << 8) | b);
}
