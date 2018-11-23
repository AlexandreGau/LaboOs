#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NBVOITURE 5
#define NBPLACES 2
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

void sleepn() {
  sleep(1. + 2. * rand() / RAND_MAX);
}

void voiture(int num, Semaphore S) {
  if (fork() == 0) {
    srand(getpid());
    P(S);
    sleepn();
    printf("%d Attend pour entrer dans le carrefour...\n", num);
    sleepn();
    printf("%d Entre dans le carrefour.\n", num);
    sleepn();
    printf("%d Sort du carrefour.\n", num);
    V(S);
    exit(0);
  }
}

int main(int argc, char *argv[]){
  Semaphore S;
  init(S, NBPLACES);

  for(int i = 0;i< NBVOITURE; i++){
    voiture(i+1, S);
  }

  for(int i = 0;i< NBVOITURE; i++){
    wait(NULL);
  }

  return 0;
}
