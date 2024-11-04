/*
 * Este programa ilustra el problema de concurrencia que se presenta al momento
 * que dos hilos intentan modificar una variable compartida.
 *
 * Ejemplo tomado del libro 'Operating Systems Three Easy Pieces'.
 *
 * Adaptado primero por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Adaptado segundo por: Jhonier Mendez - jhonier.mendez@correounivalle.edu.co
 * Fecha: 2024-11-03
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int counterglobal;
int hilos;
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
  int i = 0;

  if (argc != 3) {
        fprintf(stderr, "El programa no se escribió correctamente\n");
        printf("Debe tener la siguiente forma:\n");
printf("main <num de loops> <num de hilos>\n");
        exit(1);
  }
  max = atoi(argv[1]);
  hilos = atoi(argv[2]);

  printf("\nSe van a usar %d hilos\n", hilos);

  for (i; i < hilos; i++){
        char *num = malloc(10);
        snprintf(num, 10, "%d", i);
        pthread_t i;
        pthread_create(&i, NULL, mythread, num);
        pthread_join(i, NULL);
  }

  for(i; i < hilos; i++){
        pthread_join(i, NULL);
  }
  printf("main: begin [counter = %d] [%p]\n", counterglobal, &counterglobal);
  printf("main: done\n [counter: %d]\n [should: %d]\n",
          counterglobal, max*hilos);
  return 0;
}
