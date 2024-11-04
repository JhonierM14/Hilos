
/*
 * Este programa ilustra el problema de concurrencia que se presenta al momento
 * que dos hilos intentan modificar una variable compartida.
 *
 * Ejemplo tomado del libro 'Operating Systems Three Easy Pieces'.
 *
 * Adaptado primero por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Adaptado segundo por: Jhonier mendez - jhonier.mendez@correounivalle.edu.co
 * Fecha: 2024-11-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int counterglobal;
//volatile int counter = 0; // shared global variable

void *mythread(void *arg) {
  char *letter = arg;
  int counter = 0;
  int i; // stack (private per thread)
  printf("%s: begin [addr of i: %p]\n", letter, &i);
  for (i = 0; i < max; i++) {
        counter = counter + 1; // shared: only one
  }
  counterglobal = counterglobal + counter;
  printf("%s: done\n", letter);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
        fprintf(stderr, "El programa no se escribió correctamente\n");
        printf("Debe tener la siguiente forma:\n");
        printf("main <num de loops>\n");
        exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  printf("main: begin [counter = %d] [%p]\n", counterglobal, &counterglobal);
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");
  // join waits for the threads to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("main: done\n [counter: %d]\n [should: %d]\n",
          counterglobal, max*2);
  return 0;
}
