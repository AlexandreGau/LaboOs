#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// cat fichier1 fichier2... | fold -w 5 | tac

void closePipe(int *p){
  close(p[1]);
  close(p[0]);
}

char** setTab(char** tab, int taille){
  char** res = malloc(taille*sizeof(char*));
  res[0] = "cat";
  int i, j;
  for(i=1; i<taille-1;i++){
    res[i] = tab[i];
  }
  res[i] = NULL;
  return res;
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);

  if(fork() == 0){
    int p2[2];
    pipe(p2);
    if(fork() == 0){
      char** fichiers = setTab(argv, argc+1);
      dup2(p2[1], 1);
      closePipe(p2);
      execvp("cat",fichiers);
      free(fichiers);
    }
    wait(NULL);
    dup2(p2[0], 0);
    closePipe(p2);
    dup2(p[1], 1);
    closePipe(p);
    execlp("fold", "fold", "-w 80", NULL);
  }
  wait(NULL);
  dup2(p[0], 0);
  closePipe(p);
  execlp("tac","tac",NULL);
  return 0;
}
