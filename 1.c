#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


// LABO OS
// 172.16.113.220/vincent/f2laboos/pres/ 172.16.113.220/vincent/f2laboos/pres/pres.zip
// Séance d'introduction
// Exercices de rappels
//
// Écrire une fonction isempty prenant comme paramètre le nom d'un dossier et renvoyant true si il est vide, et false sinon.
//
// isempty DIRNAME && echo "DIRNAME is empty"

int isempty(char *dirname) {
  DIR *dir = opendir(dirname);
  struct dirent *d;
  int n = 0;

  if (dir == NULL) //Not a directory or doesn't exist
    return 1;

  while ((d = readdir(dir)) != NULL) {
    if(++n > 2)
      break;
  }

  closedir(dir);

  if (n <= 2) //Directory Empty
    return 1;
  else
    return 0;
}

int main(int argc, char *argv[]) {
  if(argc == 2){
    int rep = isempty(argv[1]);
    if(rep == 1)
      printf("%s is Empty\n", argv[1]);
    else
      printf("%s is not Empty\n", argv[1]);
  }
  return 0;
}

// By YokiDiabeul
