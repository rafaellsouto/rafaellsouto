#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;
} No;

typedef struct 
{
    No *raiz;
} Tree;

void inserirNaEsquerda( No *arvore, int valor );
void inserirNaDireita( No *arvore, int valor );
void inserir( Tree *arvores, int valor );
void imprimir( No *raiz );
int buscar( No *raiz, int chave );
No *remover( No *raiz, int chave );

int main()
{
    Tree arvoreBinariaTeste;
    arvoreBinariaTeste.raiz = NULL;
    No *raizArvore = NULL;

    inserir( &arvoreBinariaTeste, 90 );
    inserir( &arvoreBinariaTeste, 10 );
    inserir( &arvoreBinariaTeste, 1000 );
    inserir( &arvoreBinariaTeste, 100 );
    inserir( &arvoreBinariaTeste, 40 );
    inserir( &arvoreBinariaTeste, 220 );
    inserir( &arvoreBinariaTeste, 127 );
    inserir( &arvoreBinariaTeste, 2 );
    inserir( &arvoreBinariaTeste, 22 );
    
    imprimir( arvoreBinariaTeste.raiz );
    printf("\n");
    
    arvoreBinariaTeste.raiz = remover( arvoreBinariaTeste.raiz, 40 );
    arvoreBinariaTeste.raiz = remover( arvoreBinariaTeste.raiz, 1000 );
    
    imprimir( arvoreBinariaTeste.raiz );

    int res = buscar( arvoreBinariaTeste.raiz, 90 );

    if( res )
        printf("\nO valor %d está na arvore.\n", 90);
    else
        printf("\nO valor %d não está na arvore.\n", 90);

    // printf("Hello World");

    return 0;
}

void inserirNaDireita( No *arvore, int valor )
{
    if( arvore->direita == NULL )
    {
        No *novo = ( No* ) malloc( sizeof( No ) );
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arvore->direita = novo;
        
    } else {
        if( valor > arvore->direita->conteudo )
        {
            inserirNaDireita( arvore->direita, valor );
        } else {
            inserirNaEsquerda( arvore->direita, valor );
        }
    }
}

void inserirNaEsquerda( No *arvore, int valor )
{
    if( arvore->esquerda == NULL )
    {
        No *novo = ( No* ) malloc( sizeof( No ) );
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arvore->esquerda = novo;
        
    } else {
        if( valor < arvore->esquerda->conteudo )
        {
            inserirNaEsquerda( arvore->esquerda, valor );
        } else {
            inserirNaDireita( arvore->esquerda, valor );
        }
    }
}

void inserir( Tree *arvores, int valor )
{
    if( arvores->raiz == NULL )
    {
        No *novo = ( No* ) malloc( sizeof( No ) );
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arvores->raiz = novo;
        
    } else {
        if( valor < arvores->raiz->conteudo )
        {
            inserirNaEsquerda( arvores->raiz, valor );
        } else {
            inserirNaDireita( arvores->raiz, valor );
        }
        
    }
}

void imprimir( No *raiz )
{
    if( raiz )
    {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
    
}

int buscar( No *raiz, int chave )
{
    if( raiz == NULL )
    {
        return -1; 
        // return 0;
    } else {
        if( raiz->conteudo == chave )
        {
            return raiz->conteudo;
        } else {
            if( chave < raiz->conteudo )
            {
                return buscar(raiz->esquerda, chave);
            } else {
                return buscar(raiz->direita, chave);
            }
        }
    }
}

No *remover( No *raiz, int chave )
{
    if( raiz == NULL )
    {
        printf("Arvore vazia.\n\n");
        return NULL;
    } else {
        if( raiz->conteudo == chave )
        {
            // remove nós folhas, nós sem filhos
            if( raiz->esquerda == NULL && raiz->direita == NULL )
            {
                free( raiz );
                return NULL;
            } else {
                // nós com apenas um filho
                // if( raiz->esquerda != NULL || raiz->direita != NULL )
                if( raiz->esquerda == NULL || raiz->direita == NULL )
                {
                    No *aux;
                    if( raiz->esquerda != NULL )
                        aux = raiz->esquerda;
                    else 
                        aux = raiz->direita;
                    free( raiz );
                    return aux;
                } else {
                    No *aux = raiz->esquerda;
                    while( raiz->direita != NULL )
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover( raiz->esquerda, chave );
                    return aux;
                }
            }
            
            
        } else {
            if( chave > raiz->conteudo )
            {
                raiz->direita = remover( raiz->direita, chave );
            } else {
                raiz->esquerda = remover( raiz->esquerda, chave );
            }
            return raiz;
        }
    }
}
