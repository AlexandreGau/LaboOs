#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//cat fichier1 fichier2... | fold -w 5 | tac | md5sum | wc -c

void closepipe(int *p) {
  close(p[0]);
  close(p[1]);
}

void trt(int nb, char *argv[], char * args[]){
  args[0] = "cat";

  for(int i = 1; i<nb; i++){
    args[i] = argv[i];
  }

  args[nb] = NULL;
}

int main(int argc, char *argv[]){
  int p1[2];
  int p2[2];

  pipe(p1);
  pipe(p2);


  if (fork() == 0) {
    char ** args = malloc(sizeof(char*)*(argc+1));
    trt(argc, argv, args);
    dup2(p1[1], 1);
    closepipe(p1);
    execvp("cat", args);
  }


  closepipe(p2);
  pipe(p2);

  wait(NULL);

  if (fork() == 0) {
    dup2(p1[0], 0);
    dup2(p2[1], 1);
    closepipe(p1);
    closepipe(p2);
    execlp("fold","fold","-w 50",NULL);
  }

  closepipe(p1);
  pipe(p1);

  wait(NULL);

  if (fork() == 0) {
    dup2(p2[0], 0);
    closepipe(p1);
    closepipe(p2);
    execlp("tac", "tac",NULL);
  }


  closepipe(p1);
  closepipe(p2);
}
