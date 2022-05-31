#include<stdio.h>
#include<stdlib.h>

typedef struct ponto{
  int x;
  int y;
}Ponto;

void troca(Ponto*  a, Ponto* b){
  Ponto aux  = *a;
  *a = *b;
  *b =  aux;
}

//Devolve -1 se a > b
//Devolve 0 se a == b
//Devolve 1 se b > a
int compara (Ponto* a, Ponto* b){

    if (a->x > b->x || (a->x == b->x && a->y > b->y)){
        return -1;
    }
    if (b->x > a->x || (b->x == a->x && b->y > a->y)){
        return 1;
    }

    else return 0;
}

void desce_heap(Ponto* heap, int n, int pos){
  int esq = 2*pos + 1;
  int dir = 2*pos + 2;

  //Verifica se tem filhos
  if(esq >= n) return;

  int maior_filho = esq;

  //verifica se tem filho direito
  // e se ele é maior que o esquerdo
  int maior = compara (&heap[dir], &heap[maior_filho]);
  if(dir < n && maior == -1){
    maior_filho = dir;
  }
  //A função 'compara' devolve -1 se heap[maior_filho] > heap[pos]
  maior = compara (&heap[maior_filho], &heap[pos]);
  if(maior == -1){
    troca(&(heap[pos]), &(heap[maior_filho]));
    desce_heap(heap, n, maior_filho);
  }else{
    //se não tem troca, heap[pos] já tá no lugar certo.
  }
}

//recebe um vetor qualquer, e transforma em um heap
void constroi_heap(Ponto *v, int tam){
    for(int i = tam/2 ; i >= 0; i--){
      desce_heap(v, tam, i);
    }
}

// Encontra o maior ponto
Ponto extrair(Ponto *v, int tam){
  Ponto maior = v[0];
  v[0] = v[tam - 1];
  desce_heap(v, tam-1, 0);
  return maior;
}

//Ordena os pontos com o método selection sort
void selection_sort(Ponto *v, int tamanho){
    int tam = tamanho - 1;
    for (int i = 0; i < tamanho; i++){
       Ponto max = extrair(v, tamanho - i);
       troca(&max, &v[tam - i]);
    }
}

void HeapSort(Ponto *v, int tamanho){
    constroi_heap(v, tamanho);
    selection_sort(v, tamanho);
}

//************* NAO MODIFIQUE A MAIN ****************/
int main(int argc, char * argv[]){
  int tamanho;
  scanf("%d", &tamanho);
  Ponto * v = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);
  for(int i = 0; i < tamanho; i++){
    v[i].x = rand()%tamanho;
    v[i].y = rand()%tamanho;
  }

  HeapSort(v, tamanho);

  //imprimido a cada 1% (mais ou menos)
  for(int i = 0; i < tamanho; i += (tamanho/100) + 1){
    printf("(%d, %d) ", v[i].x, v[i].y);
  }
  printf("\n");
}
