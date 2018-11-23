#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void afficher(int nb){
  for(int i=0;i<nb;i++){
    printf("-");
  }
}

void listrep_recurse(char* name, int indent){
  DIR *dir = opendir(name);
  struct dirent *d;

  if (dir == NULL){
    perror("Error folder");
    closedir(dir);
    free(dir);
  }

  while((d = readdir(dir)) != NULL){
    if((d->d_type) == DT_REG){
      afficher(indent);
      printf("FILE: %s\n", d->d_name);
    }else if((d->d_type) == DT_DIR){
      if( (strcmp(d->d_name,".")!=0) && (strcmp(d->d_name, "..")!=0)){
        afficher(indent);
        printf("DIR: %s\n", d->d_name);
        char* path=malloc((sizeof(name)+sizeof(d->d_name)+1)*sizeof(char));
      	sprintf(path,"%s/%s",name,d->d_name);
      	listrep_recurse(path, indent+5);
      	free(path);
      }
    }
  }
  free(dir);
  free(d);
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    listrep_recurse(argv[1], 0);
  }
}
