#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define JETON 'c'
typedef int Semaphore[2];

void P(Semaphore S) {
  char c = JETON;
  read(S[0], &c, 1);
}

void V(Semaphore S) {
  char c = JETON;
  write(S[1], &c, 1);
}

void init(Semaphore S, int n) {
  int i;
  char c = JETON;

  pipe(S);
  for (i = 0; i < n; i++) {
    write(S[1], &c, 1);
  }
}

void writechar(char c1, char c2, int n, Semaphore S){
  if(fork() == 0){
    for(int i=0;i<n;i++){
      P(S);
      write(1, &c1, 1);
      write(1, &c2, 1);
      V(S);
    }
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  Semaphore S;
  init(S, 1);

  writechar('A', 'B', 100, S);
  writechar('1', '2', 100, S);

  wait(NULL);
  wait(NULL);

  return 0;
}
