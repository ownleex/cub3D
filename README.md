# Cub3D - Premier Ray-caster

## Description
Cub3D est un projet de visualisation 3D inspiré du jeu Wolfenstein 3D, considéré comme le premier FPS de l'histoire. Ce projet met en œuvre la technique du ray-casting pour créer une représentation 3D d'un labyrinthe à partir d'une carte 2D.

Le programme permet de se déplacer dans un environnement 3D, avec des textures différentes selon l'orientation des murs (nord, sud, est, ouest), ainsi que des couleurs configurables pour le sol et le plafond.

## Fonctionnalités

### Partie Obligatoire
- Rendu 3D d'un labyrinthe défini par un fichier de carte
- Textures différentes selon l'orientation des murs (nord, sud, est, ouest)
- Couleurs personnalisables pour le sol et le plafond
- Déplacement avec WASD et rotation de la caméra avec les flèches gauche/droite
- Gestion propre de la fermeture du programme (touche ESC ou clic sur la croix)
- Parsing de fichier de carte au format .cub

### Fonctionnalités Bonus
- Collision avec les murs
- Système de mini-carte
- Portes qui peuvent être ouvertes/fermées
- Animations (textures animées)
- Rotation de la caméra avec la souris

## Compilation

### Prérequis
- GCC ou Clang
- Make
- Bibliothèque MinilibX (fournie dans le repo)
- Bibliothèques X11 et Xext pour Linux

### Instructions de compilation
```bash
# Compiler la version standard
make

# Compiler la version avec les bonus
make bonus
```

## Utilisation

### Exécution
```bash
# Version standard
./cub3D maps/map1.cub

# Version avec bonus
./cub3D_bonus maps/map4.cub
```

### Format du fichier de carte (.cub)
Le fichier de carte doit contenir les éléments suivants :
- Chemins vers les textures des murs (NO, SO, WE, EA)
- Couleurs du sol (F) et du plafond (C) au format R,G,B
- La carte du labyrinthe elle-même, composée des caractères suivants :
  - `0` : Espace vide
  - `1` : Mur
  - `N`, `S`, `E`, `W` : Position et orientation initiales du joueur
  - `D` : Porte (uniquement dans la version bonus)

Exemple de fichier .cub :
```
NO ./textures/set1/north.xpm
SO ./textures/set1/south.xpm
WE ./textures/set1/west.xpm
EA ./textures/set1/east.xpm

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
1111111110110000011100001
10000000001100000111011111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000000001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Contrôles
- `W`, `A`, `S`, `D` : Déplacement du joueur
- `←`, `→` : Rotation de la caméra
- `ESC` : Quitter le programme
- `E` : Ouvrir/fermer les portes (version bonus)
- `TAB` : Activer/désactiver le contrôle de la caméra par la souris (version bonus)

## Structure du projet
```
.
├── include/          # Fichiers d'en-tête
├── libft/            # Bibliothèque personnelle
├── maps/             # Cartes de jeu
├── mlx_linux/        # MinilibX pour Linux
├── src/              # Code source
│   ├── bonus/        # Implémentation des bonus
│   └── ...           # Fichiers source principaux
├── textures/         # Textures du jeu
│   ├── set1/
│   ├── set2/
│   ├── ...
├── Makefile          # Fichier de compilation
└── README.md         # Ce fichier
```

## Crédits
Ce projet a été développé en collaboration avec [ElkiaCode](https://github.com/ElkiaCode) dans le cadre du cursus de l'école 42.