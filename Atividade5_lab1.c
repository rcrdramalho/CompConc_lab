#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

int *v, M, N;

void *soma_um(void *arg) {
    int id = *(int *)arg;
    int div = N / M;

    if(id == M-1){
        for(int i = id*div; i < N; i++) {
        v[i] += 1;
        }
    }else{
        for(int i = id*div; i < (id+1)*div; i++) {
        v[i] += 1;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    if(argc < 3) {
       printf("--ERRO: informe a qtde de threads <%s> <nthreads>\n", argv[0]);
       return 1;
    }

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    v = (int *)malloc(N * sizeof(int));


    pthread_t tid[M];
    int indice[M];

    // Preenche o vetor com 0, 10, 20, 30...
    for(int i = 0; i < N; i++) {
        v[i] = i * 10;
    }
    printf("Vetor inicial:\n");
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

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
    printf("Vetor final:\n");
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n--Thread principal terminou\n");

    free(v);
    return 0;
}
