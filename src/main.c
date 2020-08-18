/* Raphael Carvalho - RA: 205125
 * Laboratório 05 - Cotador de primos com multithreads
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 4

/*======= Variaveis Globais ======= */
int primes; // contar números primos
pthread_mutex_t lock;
int input; // entrada a ser colocada pelo programa
/* ================================ */

/* funcao simples que detecta se um número eh ou nao primo.
* retorna 0 se nao primo
* retorna 1 se primo
*/
int prime_number(int number)
{
	int j; //variavel auxiliar para calculo de numeros primos 

	if(number == 0 || number == 1)
 		return 0; // caso o numero seja 0 ou 1, considera-se nao primo

	/* loop para testar se num eh divisel por outro num alem dele mesmo */
	for(j = 2; j < number; j++)	
	{
		if(number % j == 0)
			return 0;
	}

	return 1;	// numero eh primo	
}

/* funcao thread */
void* worker(void *arg)
{
	int* num = (int*)arg;
	int number_eval = (*num); // numero a ser avaliado	
	
	/* travar a thread */
	pthread_mutex_lock(&lock);
	
	/* avaliar se o numero eh ou nao primo */
	primes += prime_number(number_eval);
	
	/* destravar a thread */ 
	pthread_mutex_unlock(&lock);
	
	return NULL;
}


int main() 
{
	pthread_t threads[MAX_THREADS]; // quantidade max de threads que podem executar
	int thread_counter = 0; // contar qunatas threads existem
	int aux = 0; // variavel auxiliar	
	
	primes = 0; // inicializar a quantidade de numeros primos
	
	do
	{
		if(thread_counter < MAX_THREADS) // enquanto houver menos do que 4 threads
		{
			scanf("%d", &input); // ler a entrada 
			
			/* criar a thread */
			pthread_create(&(threads[thread_counter]), NULL, worker, &input);
		}
		
		/* tempo para a thread */
		sleep(1); 
		
		thread_counter++; // contador do numero de threads
		
		/* quando chegamos a 4 threads, espera uma continuar */	
		if(thread_counter == 4)
		{ 
  			pthread_join(threads[thread_counter - 1], NULL);
  			thread_counter--;	
		}
		
	}while((input = getchar()) != '\n');
	
	/* esperar todas asthreads encerrarem */
	for (int i = 0; i < MAX_THREADS; i++) 
	{
    	pthread_join(threads[i], NULL);
  	}
  	
  	printf("%d\n", primes);
	
	return 0;
}






