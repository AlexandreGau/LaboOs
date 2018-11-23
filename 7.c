#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

void closePipe(int *p){
  close(p[1]);
  close(p[0]);
}

int main(int argc, char** argv){

  int p[2];
  pipe(p);

  if (fork() == 0) {
    dup2(p[1], 1);
    closePipe(p);
    execlp("tac","tac", "commandeEmacs.txt", NULL);
  }
  wait(NULL);

  dup2(p[0], 0);
  closePipe(p);
  execlp("fold","fold","-w 80", NULL);
  return(0);
}
