#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

int *v, M, N;

void *soma_um(void *arg) {
    //Usa o argumento para identificar em qual thread estamos trabalhando e ela começar do elemento correspondente a ela.
    int id = *(int *)arg;
    int div = N / M;
    int inicio, fim;
    int res = N % M;

    if (id < res) {
        //Caso o indice tenha passado o numero de threads que calcularao mais elementos executa apenas N/M elementos.
        inicio = id * (div + 1);
        fim = inicio + div + 1;
    } else {
        //Caso contrário executa N/M + 1 (resto) elementos.
        inicio = id * div + res;
        fim = inicio + div;
    }

    for (int i = inicio; i < fim; i++) {
        v[i] += 1;
    }

    pthread_exit(NULL);
}

void checaVetor(){
    int erros=0;
    for(int i = 0; i < N; i++) {
        if(v[i]!= (i*10 + 1)){
            erros++;
        }
    }
    printf("Total de %i erros\n", erros);
    //Varre todo o vetor para checar se está tudo certo. 
}

int main(int argc, char* argv[]) {

    if(argc < 3) {
       printf("--ERRO: informe a qtde de threads <%s> <nthreads>\n", argv[0]);
       return 1;
    }

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    v = (int *)malloc(N * sizeof(int));
    if (v == NULL) {
      printf("--ERRO: malloc()\n"); 
      return 1;
    }

    pthread_t tid[M];
    int indice[M];

    // Preenche o vetor com 0, 10, 20, 30...
    for(int i = 0; i < N; i++) {
        v[i] = i * 10;
        //printf("%i ", v[i]);
    }


    printf("Vetor inicial com %i elementos ordenados multiplos de 10.\n", N);

    //Execução das M threads
    for(int i = 0; i < M; i++) {
        indice[i] = i;
        if (pthread_create(&tid[i], NULL, soma_um, (void *)&indice[i])) {
        printf("--ERRO: pthread_create()\n"); 
        return 2;
    }
    }
    for (int i=0; i<M; i++) {
        if (pthread_join(tid[i], NULL)) {
            printf("--ERRO: pthread_join() da thread %d\n", i); 
        } 
    }

    //Resultado
    checaVetor();

    for(int i = 0; i < N; i++) {
        //printf("%i ", v[i]);
    }

    printf("\n--Thread principal terminou\n");

    

    free(v);
    return 0;
}
