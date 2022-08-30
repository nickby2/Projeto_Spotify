#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int leLinha (void) {
int c;
int nlinhas = 0; /* contador do número de linhas */
FILE *fp;
/* abre arquivo para leitura */
//fp = fopen("Reviews_modified.csv","r+"); //(Lê o número de linhas pro dataset inteiro)
fp = fopen("Graph_data.csv","rt");
if (fp==NULL) {
printf("Não foi possivel abrir arquivo.\n");
return 1;
}
/* lê caractere a caractere */
while ((c = fgetc(fp)) != EOF) {
if (c == '\n')
nlinhas++;
}
/* fecha arquivo */
fclose(fp);
/* exibe resultado na tela */
printf("Numero de linhas = %d\n", nlinhas);
return nlinhas;
}

void swap(float *a, float *b) {
  float t = *a;
  *a = *b;
  *b = t;
}

int partition(float array[], int low, int high) {
  
  int pivot = array[high];
  
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      i++;
      
  
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  
  return (i + 1);
}

void quickSort(float array[], int low, int high) {
  if (low < high) {
    

    int pi = partition(array, low, high);
    

    quickSort(array, low, pi - 1);
    

    quickSort(array, pi + 1, high);
  }
}


void printArray(float array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%f  ", array[i]);
  }
  printf("\n");
}

int main() {

  clock_t inicio = clock();
  
  FILE *fp;

  int tam = leLinha();

  int dia, hora1, hora2, hora3;
  int i, ano, mes, data_aux[tam], mes_aux[tam];
  float data[tam];

  //fp = fopen("Reviews_modified.csv","r+"); //(Abre o arquivo do dataset completo)
  fp = fopen("Graph_data.csv","r+");
    if (fp == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

  for(i = tam - 1; i >= 0; i--){
  //fscanf(fp, "%d-%d-%d %d:%d:%d,%f\n", &ano, &mes, &dia, &hora1, &hora2, &hora3, &data[i]); //(Scaneia o dataset completo)
  fscanf(fp, "%d%*c %d%*c %f", &ano, &mes, &data[i]);
  data_aux[mes - 1] = data[i];
  printf("%d\n", mes);
  printf("%f\n", data[i]);
  }
  
  //printf("Vetor desordenado: \n"); //(Opção para ver o vetor antes da ordenação)
  printArray(data, tam);
  
  quickSort(data, 0, tam - 1);
  
  //printf("Vetor ordenado: \n"); ////(Opção para ver o vetor depois da ordenação)
  printArray(data, tam);
  
fclose(fp);

clock_t fim = clock();

double tempofin = (double) (fim - inicio) / CLOCKS_PER_SEC;

printf("\nTempo de execução: %fs\n", tempofin);

return 0;  
}
