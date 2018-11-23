#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Exercice 13: Lorsqu'un nageur arrive à la piscine, il doit prendre un panier, aller à la cabine pour se déshabiller,
// nager, entrer dans une autre cabine pour se rhabiller, puis rendre le panier.
// Créez une méthode nageur(int num, Semaphore S) réalisant le comportement d'un nageur.
// Créez ensuite NBNAGEURS nageurs, sachant qu'il n'y a que NBCABINES et NBPANIERS.

#define JETON 'c'
#define NBNAGEURS 4
#define NBCABINES 3
#define NBPANIERS 2
typedef int Semaphore[2];

void P(Semaphore S){
  char c = JETON;
  read(S[0], &c, 1);
}

void V(Semaphore S){
  char c = JETON;
  write(S[1], &c, 1);
}

void init(Semaphore S, int n){
  char c = JETON;
  pipe(S);

  for(int i=0;i<n;i++){
    write(S[1], &c, 1);
  }
}

void sleepn(){
  sleep(1. + 2. * rand() / RAND_MAX);
}

void nageur(int n, Semaphore S1, Semaphore S2){
  if(fork() == 0){
    srand(getpid());
    sleepn();
    P(S1);
    printf("%d Prend panier\n", n);
    sleepn();
    P(S2);
    printf("%d Entrer cabine pr desha.\n", n);
    sleepn();
    V(S2);
    printf("%d nage.\n", n);
    sleepn();
    P(S2);
    printf("%d Entre cabine pr rhab.\n", n);
    sleepn();
    V(S2);
    printf("%d Rend panier.\n", n);
    V(S1);
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  Semaphore S1;
  Semaphore S2;
  init(S1,NBPANIERS);
  init(S2,NBCABINES);

  for(int i=0; i<NBNAGEURS;i++){
    nageur(i, S1, S2);
  }

  for(int i = 0;i< NBNAGEURS; i++){
    wait(NULL);
  }

  return 0;
}
