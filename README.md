# Doom-Nukem
Un melange de Doom et Duke Nukem 3D.

L'objectif de ce projet est de nous faire réaliser entièrement un moteur graphique 3D en utilisant la méthode du Raycasting.

Le sujet est disponible [ici](https://github.com/qpupier/Doom-Nukem/blob/master/Sujet.pdf).

**Autres contributeurs :**
>- [Slopez](https://github.com/sylrelo)
>- [Asaba](https://github.com/AdleneS)
>- [Lulemair](https://github.com/LudovicLemaire)

## Contraintes du projet
Groupe de 3 à 4 étudiants.

**Fonctions de la libc autorisées :**
>- malloc
>- free
>- perror
>- strerror
>- exit

**Librairies autorisées** :
>- MinilibX (Librairie graphique de 42 contenant uniquement des fonctions standard d'affichage de pixels et de gestion d'évennements)
>- [Libft](https://github.com/qpupier/Doom-Nukem/blob/master/libft) (Projet de 42 réalisé précédemment contenant notre propre version des fonctions de la libc dont nous avons besoin, plus d'autres fonctions créées par nos soins)
>- math (-lm)
>- OpenAL (pour parser nous même sos sons)

**Tout les appels systèmes sont autorisé**

## Installation
````bash
git clone https://github.com/Sylrelo/42-Doom-Nukem.git
make
````
## Utilisation
````bash
./doom-nukem [--pack] [map_file]
./DoomMapEditor
````
