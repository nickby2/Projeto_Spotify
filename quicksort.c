#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int leLinha (void) {
int c;
int nlinhas = 0; /* contador do número de linhas */
FILE *fp;
/* abre arquivo para leitura */
fp = fopen("Reviews_modified.csv","r+");
//fp = fopen("Graph_data.csv","rt");
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

// function to find the partition position
int partition(float array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(float array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// function to print array elements
void printArray(float array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%f  ", array[i]);
  }
  printf("\n");
}

int escreve() {
  
}

// main function
int main() {

  clock_t inicio = clock();
  
  FILE *fp;

  int tam = leLinha();

  int dia, hora1, hora2, hora3;
  int i, ano, mes, data_aux[tam], mes_aux[tam];
  float data[tam];

  fp = fopen("Reviews_modified.csv","r+");
  //fp = fopen("Graph_data.csv","r+");
    if (fp == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

  for(i = tam - 1; i >= 0; i--){
  fscanf(fp, "%d-%d-%d %d:%d:%d,%f\n", &ano, &mes, &dia, &hora1, &hora2, &hora3, &data[i]);
  //fscanf(fp, "%d%*c %d%*c %f", &ano, &mes, &data[i]);
  data_aux[mes - 1] = data[i];
  printf("%d\n", mes);
  printf("%f\n", data[i]);
  }
  
  printf("Unsorted Array\n");
  printArray(data, tam);
  
  // perform quicksort on data
  quickSort(data, 0, tam - 1);
  
  printf("Sorted array in ascending order: \n");
  printArray(data, tam);
  
fclose(fp);

clock_t fim = clock();

double tempofin = (double) (fim - inicio) / CLOCKS_PER_SEC;

printf("\nTempo de execução: %fs\n", tempofin);

return 0;  
}
