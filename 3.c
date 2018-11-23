#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

// Exercice: Créer une fonction qui prend en paramètre le chemin d'un fichier, et affiche:
//     si le fichier passé en paramètre est un fichier régulier:
//     file: NOM DU FICHIER
//     si le fichier passé en paramètre est un dossier:
//     folder: NOM DU DOSSIER

int main(int argc, char const *argv[]) {
  DIR *dir = opendir(argv[1]);

  if (dir == NULL){
    printf("File : %s\n", argv[1]);
  }else{
    printf("Folder : %s\n", argv[1]);
  }

  return 0;
}
