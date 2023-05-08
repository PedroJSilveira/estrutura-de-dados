#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"

int main() {
    char nomeArquivo[30];
    arvore *arv;
    int elemRem;

    scanf("%s", nomeArquivo);

    arv = criaArvore();
    printf("ARVORE CRIADA\n");
    processaCarga(arv, nomeArquivo);
    printf("PROCESSA CARGA OK\n");
    imprimePreOrdem(getRaiz(arv));
    printf("\nIMPREÇÃO EM PREORDEM OK");
    printf("\n%d\n", getNumElementos(arv));
    printf("GET NUM OK\n");

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    imprimePreOrdem(getRaiz(arv));
    printf("\n%d\n", getNumElementos(arv));

    scanf("%d", &elemRem);
    if (removeNo(arv, elemRem) == -1)
        printf("Elemento não esta na arvore");

    free(arv);

return 0;
}
