#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#define N_THREADS 4 //Maximo de 4 threads
int b=0, fim=0;
int a;
char c;
pthread_mutex_t trava;
void* funcao_thread(void *arg) { //Funcao para encontrar numero primo
	int* N = (int*)arg;
	int M = (*N);
	int i, div; 
	pthread_mutex_lock(&trava);
	if (fim==1) { //Se ja encontrou fim, libera mutex e encerra
		pthread_mutex_unlock(&trava);
		return NULL;
		}	
	scanf("%d%c", &a, &c); //Procura um inteiro, seguido de um char
			if (c == '\n') fim=1;	//Se o char for fim de linha, marca flag de fim de programa
      for (div=0, i = 1; i <= a; i++) { //Loop para descobrir se e numero primo
      if (a % i == 0) {
				div++;
				}
      }
  if (div == 2)	b+=1; //b armazena a quantidade de numeros primos encontrados
pthread_mutex_unlock(&trava);
  return NULL;
}

int main() {
	pthread_t threads[N_THREADS];
	int thread_args[N_THREADS];
 	if( pthread_mutex_init(&trava, NULL) != 0){
 		fprintf(stderr, "Erro ao criar mutex.\n");
 		exit(EXIT_FAILURE);
 	}
	while(1){
	if (fim==1) break;
	// Executa ate 4 threads simultaneamente, entao espera ate que as 4 terminem e repete
	//o processo ate que a flag de fim de programa seja acionada
  for (int i=0; i<N_THREADS; i++) {
		if (fim==1) break;
    	thread_args[i] = i;
			pthread_create(&(threads[i]), NULL, funcao_thread, &(thread_args[i]));
	}
    for (int i=0; i <N_THREADS; i++) { //espera as 4 threads se encerrarem			
    	pthread_join(threads[i], NULL);
			}
  }
	printf("%d\n", b);
	pthread_mutex_destroy(&trava);
  return 0;

}
