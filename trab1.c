#include<stdio.h>
#include<stdlib.h>

typedef struct ponto{
  int x;
  int y;
}Ponto;

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

//Devolve o indice do maior elemento, obrigatoriamente
//Deve usar a função compara
//dir = tamanho - 1
int encontra_max(Ponto *v, int esq, int dir){
    int maior = esq;
    for (int i = esq+1; i <= dir; i++){
        int result = compara (&v[i], &v[maior]);
          if (result == -1){
            maior = i;
        } if (result == 1){
            maior = maior;
        } if (result == 0){
            maior = i;
        }
    }
    return maior;
}

//Ordena os pontos, obrigatoriamente deve usar a função
//encontra_max
void selection_sort(Ponto *v, int tamanho){
    Ponto aux;
    int tam = tamanho - 1;
    for (int i = 0; i < tamanho; i++){
       int max = encontra_max(v, 0, tam -i);
       aux.x = v[tam -i].x;
       aux.y = v[tam -i].y;
       v[tam -i].x = v[max].x;
       v[tam -i].y = v[max].y;
       v[max].x = aux.x;
       v[max].y = aux.y;
    }
}

int main(int argc, char * argv[]){
  int tamanho;
  scanf("%d", &tamanho);
  Ponto * v = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);
  for(int i = 0; i < tamanho; i++){
    v[i].x = rand()%tamanho;
    v[i].y = rand()%tamanho;
  }

  int indice_maior = encontra_max(v, 0, tamanho-1);
  printf("O maior é (%d, %d) ", v[indice_maior].x, v[indice_maior].y);
  printf("\n");

  selection_sort(v, tamanho);

  for(int i = 0; i < tamanho; i++){
    printf("(%d, %d) ", v[i].x, v[i].y);
  }
  printf("\n");
}

