#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

// Créez une fonction rmdirifempty supprimant la variable passée an paramètre si celle-ci est un dossier et que ce dossier est vide.
// En cas d'erreur, affiche un message sur la sortie d'erreur avec une valeur retour valant 1.
//    Si aucun paramètre passé en argument, affiche
//    rmdirifempty: opérande manquant
//
//    Si le paramètre n'est pas un dossier, affiche
//    rmdirifempty: « ARG » n'est pas un dossier
//
//    Si le dossier n'est pas vide: affiche
//    rmdirifempty: « ARG » n'est pas vide
//
// Sinon, affiche:
// « ARG » supprimé.
// et renvoie la valeur 0.

void rmdirifempty(char* nom){
  DIR *dir = opendir(nom);
  struct dirent *d;

  if( dir == NULL ){
    printf("rmdirifempty: %s n'est pas un dossier\n", nom);
    return;
  }

  int n = 0;
  while ((d = readdir(dir)) != NULL) {
    if(n++ > 2)
      break;
  }

  closedir(dir);

  if (n <= 2){ //Directory Empty
    rmdir(nom);
    printf("%s supprimé\n", nom);
  }else{
    printf("rmdirifempty: %s n'est pas vide\n", nom);
  }
}

int main(int argc, char *argv[]) {
  if(argc == 2){
    rmdirifempty(argv[1]);
  }else
    printf("rmdirifempty: opérante manquant\n");

  return 0;
}

//By YokiDiabeul
