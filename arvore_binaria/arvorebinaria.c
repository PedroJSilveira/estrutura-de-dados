#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"


struct no
{
    int chave;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};

struct arvore
{
    struct no *sentinela;
    int numElemento;
};


void processaCarga(arvore *arv, char *nomeArquivo){
    FILE *arq;
    int valor;

    arq = fopen(nomeArquivo, "r");

    if(arq == NULL){
      return;
    }
    
    while (!feof(arq))
    {
        fscanf(arq, "%d", &valor);
        insereNo(arv, valor);
        arv->numElemento++;
    }
      
}


arvore *criaArvore(){
    arvore *arv;
   
    arv = (arvore*) malloc (sizeof(arvore));
    arv->sentinela = (no*) malloc (sizeof(no));

    if (arv != NULL){
        arv->sentinela->Fesq = NULL;
        arv->sentinela->Fdir = NULL;
        arv->sentinela->chave = -1000;
        arv->numElemento = 0;
    }

    return arv;
}

int insereNo (arvore *arv, int valor){
    //verifica se a arvore foi criada corretamente
    if (arv == NULL)
        return 0;

    no *aux;
    aux = (no*) malloc (sizeof(no));

    //verifica se o nó foi criado corretamente
    if (aux == NULL)
        return 0;

    //atribuindo valores ao nó
    aux->chave = valor;
    aux->Fdir = NULL;
    aux->Fesq = NULL;

    //caso a arvore não possua nós, atribui o nó a raiz
    if (arv->sentinela->Fesq == NULL){
        arv->sentinela->Fesq = aux;
        aux->pai = arv->sentinela;
    }

    //caso contrario percorre a arvore e insere o elemento ordenado
    else{
        no *atual = arv->sentinela->Fesq;
        no *anterior = NULL;

        //percorrendo a arvore
        while (atual != NULL)
        {
            anterior = atual;
            if (valor < atual->chave)
                atual = atual->Fesq;

            else 
                atual = atual->Fdir;
        }

        //inserindo o valor na arvore 
        if (valor < anterior->chave){
            anterior->Fesq = aux;
            aux->pai = anterior;
        }
        else{
            anterior->Fdir = aux;    
            aux->pai = anterior;
        }
    }

    return 1;
}


int removeNo(arvore *arv, int valor){
     if (arv->sentinela->Fesq == NULL)
    {
        return 0;
    }
    no *atual = arv->sentinela->Fesq;
    no *pai_atual = arv->sentinela;

    while (atual != NULL && atual->chave != valor)
    {
        pai_atual = atual;
        if (valor < atual->chave)
        {
            atual = atual->Fesq;
        }
        else
        {
            atual = atual->Fdir;
        }
    }
    if (atual == NULL)
    {
       return -1;
    }

    if (atual->Fesq == NULL || atual->Fdir == NULL)
    {
        no *filho = NULL;
        if (atual->Fesq != NULL)
        {
            filho = atual->Fesq;
        }
        else
        {
            filho = atual->Fdir;
        }
        if (filho == NULL)
        {
            // caso em que o nó a ser removido não tem filhos
            if (atual == arv->sentinela->Fdir)
            {
                // remove a raiz da árvore vazia
                arv->sentinela->Fdir = NULL;
            }
            else
            {
                // remove o nó folha
                if (pai_atual->Fesq == atual)
                {
                    pai_atual->Fesq = NULL;
                }
                else
                {
                    pai_atual->Fdir = NULL;
                }
                atual->pai = NULL;
            }
            free(atual);
        }
        else
        {
            // caso em que o nó a ser removido tem um filho
            if (atual == arv->sentinela->Fdir)
            {
                // remove a raiz da árvore
                arv->sentinela->Fdir = filho;
                filho->pai = arv->sentinela;
            }
            else
            {
                // remove um nó interno
                if (pai_atual->Fesq == atual)
                {
                    pai_atual->Fesq = filho;
                }
                else
                {
                    pai_atual->Fdir = filho;
                }
                filho->pai = pai_atual;
                atual->pai = NULL;
            }
            free(atual);
        }
    }
    else
    {
        // caso em que o nó a ser removido tem dois filhos
        no *sucessor = atual->Fdir;
        no *pai_sucessor = atual;
        while (sucessor->Fesq != NULL)
        {
            pai_sucessor = sucessor;
            sucessor = sucessor->Fesq;
        }

        atual->chave = sucessor->chave;
        if (pai_sucessor == atual)
        {
            pai_sucessor->Fdir = sucessor->Fdir;
        }
        else
        {
            pai_sucessor->Fesq = sucessor->Fdir;
        }

        if (sucessor->Fdir != NULL)
        {
            sucessor->Fdir->pai = pai_sucessor;
        }
        free(sucessor);
    }
    arv->numElemento--;
    return 1;
}

no *getRaiz (arvore *arv){
    return arv->sentinela->Fesq;
}

int getNumElementos(arvore *arv){
    return arv->numElemento;
}

void imprimeOrdem(no *arv){
    if (arv != NULL){
        imprimeOrdem(&(*(arv)->Fesq));
        printf("%d - %d\n",arv->chave, arv->pai->chave);
        imprimeOrdem(&(*(arv)->Fdir));
    }
}

void imprimePreOrdem(no *arv){
    if (arv != NULL){
        printf("%d - %d\n",arv->chave, arv->pai->chave);
        imprimePreOrdem(&(*(arv)->Fesq));
        imprimePreOrdem(&(*(arv)->Fdir));
    }
    else return;
} 