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
int compara(Ponto * a, Ponto * b){
    if (a->x > b->x){
        return -1;
    } else

    if (b->x > a->x){
        return 1;
    } else

    if (a->x == b->x && a->y == b->y){
        return 0;
    } else

    if (a->x == b->x){
        if (a->y > b->y){
            return -1;
    }   if (b->y > a->y){
        return 1;
        }
    }

    return 2;
}

void sobe_heap(Ponto* heap, int pos){
  if(pos == 0) return;
  int pai = (pos-1)/2;
  //EXISTE UMA INVERSAO?
  int maior = compara(&heap[pos],&heap[pai]);
  //A função 'compara' devolve -1 se heap[pos] > heap[pai]
  if(maior == -1){
    troca(&(heap[pos]), &(heap[pai]));
    sobe_heap(heap, pai);
  }else {
    //Se não tem inversao nao faz nada.
  }
}

void insere(Ponto* heap, int pos, Ponto  p){
  heap[pos] = p;
  sobe_heap(heap, pos);
  return;
}

void desce_heap(Ponto* heap, int n, int pos){
  int esq = 2*pos + 1;
  int dir = 2*pos + 2;

  //tenho filhos?
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

Ponto extrair(Ponto *heap, int pos){
  Ponto maior = heap[0];
  heap[0] = heap[pos-1];
  desce_heap(heap, pos-1, 0);
  return maior;
}

int main(int argc, char* argv[]){
  int tamanho, tam_atual = 0;
  scanf("%d", &tamanho);

  Ponto * heap = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);

  printf("Inserindo %d pontos\n", tamanho/2);
  for(int i = 0; i < tamanho/2; i++, tam_atual++){
    int x = rand()%tamanho;
    int y = rand()%tamanho;
    Ponto  p;
    p.x = x;
    p.y = y;
    insere (heap, tam_atual, p);
  }

  printf("Extraindo os %d maiores\n", tamanho/4);
  for(int i = 0; i < tamanho/4; i++, tam_atual--){
      //FAZER: Extrair e imprimir
      Ponto maior = extrair(heap, tam_atual);
      printf("(%d, %d) ", maior.x, maior.y);
  }

  printf("\n");

  printf("Inserindo %d pontos\n", 3*tamanho/4);
  for(int i = 0; i < 3*tamanho/4; i++, tam_atual++){
    int x = rand()%tamanho;
    int y = rand()%tamanho;
    //FAZER: AQUI VOCE INSERE O PONTO (x, y) no heap
    Ponto  p;
    p.x = x;
    p.y = y;
    insere (heap, tam_atual, p);
  }

  printf("Extraindo os %d maiores\n", tamanho/2);
  for(int i = 0; i < tamanho/2; i++, tam_atual--){
      Ponto maior = extrair(heap, tam_atual);
      printf("(%d, %d) ", maior.x, maior.y);
  }

  printf("\n");

  free (heap);

  return 0;
}



