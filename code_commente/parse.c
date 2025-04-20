
#include "cub3d.h"

/*
** Ouvre le fichier de configuration
** param file_path: Chemin vers le fichier de configuration
** return: Descripteur de fichier, ou -1 en cas d'erreur
*/
int open_file(char *file_path)
{
    int fd;
    
    // Vérifier que le chemin n'est pas NULL
    if (!file_path)
        return (-1);
    
    // Ouvrir le fichier en lecture seule
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nCould not open file: %s\n", file_path);
        return (-1);
    }
    
    return (fd);
}

/*
** Charge le contenu du fichier en mémoire
** param game: Pointeur vers la structure principale du jeu
** param fd: Descripteur de fichier ouvert
** return: true si le chargement a réussi, false sinon
*/
bool load_file_content(t_game *game, int fd)
{
    char *line;
    char *content;
    char *temp;

    // Initialiser le contenu avec une chaîne vide
    content = ft_strdup("");
    if (!content)
        return (false);
    
    // Lire le fichier ligne par ligne
    line = get_next_line(fd);
    while (line)
    {
        // Sauvegarder l'ancien contenu
        temp = content;
        // Concaténer la nouvelle ligne au contenu
        content = ft_strjoin(content, line);
        // Libérer l'ancien contenu et la ligne lue
        free(temp);
        free(line);
        
        // Vérifier que la concaténation a réussi
        if (!content)
            return (false);
        line = get_next_line(fd);
    }
    
    // Diviser le contenu en tableau de lignes
    game->file = ft_split(content, '\n');
    
    // Libérer le contenu complet maintenant que nous avons le tableau
    free(content);
    
    // Vérifier que la division a réussi
    if (!game->file)
        return (false);
    
    return (true);
}

/*
** Fonction principale d'analyse du fichier de configuration
** param game: Pointeur vers la structure principale du jeu
** param file_path: Chemin vers le fichier de configuration (.cub)
** return: true si l'analyse a réussi, false sinon
*/
bool parse_file(t_game *game, char *file_path)
{
    int fd;
    
    // Ouvrir le fichier de configuration
    fd = open_file(file_path);
    if (fd < 0)
        return (false);
    
    // Charger le contenu du fichier en mémoire
    if (!load_file_content(game, fd))
    {
        close(fd);
        return (false);
    }
    close(fd);
    
    // Analyser les textures et couleurs définies dans le fichier
    if (!parse_textures(game))
        return (false);
    
    // Analyser la carte définie dans le fichier
    if (!parse_map(game))
        return (false);
    
    return (true);
}