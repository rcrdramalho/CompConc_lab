/*
Programa auxiliar para gerar um vetor de floats e seu produto interno
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000 //valor maximo de um elemento do vetor
//#define PRINTAR

float elemento_aleatorio(){
   
   float fator, elem;

   fator = ((rand() % 2) == 1 ? 1 : -1);
   elem = (rand() % MAX)/3.0 * fator;

   return(elem);
}

int main(int argc, char*argv[]) {
   float *vetor1; //vetor que será gerado
   float *vetor2; //vetor que será gerado
   long int n; //qtde de elementos do vetor que serao gerados
   double produto=0; //produto interno dos dois vetores
   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <arquivo saida>\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);

   //aloca memoria para o vetor
   vetor1 = (float*) malloc(sizeof(float) * n);
   if(!vetor1) {
      fprintf(stderr, "Erro de alocao da memoria do vetor\n");
      return 2;
   }
   vetor2 = (float*) malloc(sizeof(float) * n);
   if(!vetor2) {
      fprintf(stderr, "Erro de alocao da memoria do vetor\n");
      return 2;
   }

   //preenche o vetor com valores float aleatorios
   srand(time(NULL));
   for(long int i=0; i<n; i++) {
      vetor1[i] = elemento_aleatorio();
      vetor2[i] = elemento_aleatorio();
      produto += vetor1[i]*vetor2[i]; //acumula o elemento na soma total
   }

   //escreve o vetor no arquivo
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve a dimensao
   ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);
   //escreve os elementos do vetor1
   ret = fwrite(vetor1, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   //escreve os elementos do vetor1
   ret = fwrite(vetor2, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   //escreve o produto
   ret = fwrite(&produto, sizeof(double), 1, descritorArquivo);

   #ifdef PRINTAR
   fprintf(stdout, "%ld\n", n);
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor1[i]);
   }
   fprintf(stdout, "\n");
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor2[i]);
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "produto=%lf\n", produto);
   #endif

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(vetor1);
   free(vetor2);
   return 0;
} 
