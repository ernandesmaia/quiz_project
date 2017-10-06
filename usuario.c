#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "interacao.h"

struct arv{
    ArvNo* raiz;
};

struct arvno{
    Usuario* usuario;
    ArvNo* esq;
    ArvNo* dir;
};

struct usuario{
    char nome[51];
    int perfil;
    int id;
    char login[21];
    char senha[21];
};

Usuario* usu_cria(char* nome, int perfil, int id, char* login, char* senha)
{
    Usuario* u = (Usuario*) malloc(sizeof(Usuario));
    if(u == NULL){
        printf("Memoria insuficiente - 'usu_cria' - programa sendo fechado!\n");
        exit(1);
    }
    strcpy(u->nome, nome);
    u->perfil = perfil;
    u->id = id;
    strcpy(u->login, login);
    strcpy(u->senha, senha);
    return u;
}


static ArvNo* insere(ArvNo* a, Usuario* u)
{
    if(a == NULL){
        ArvNo* a = (ArvNo*) malloc(sizeof(ArvNo*));
        if(a == NULL){
            printf("erro - 'insere'\n");
            exit(1);
        }
        a->usuario = u;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    if(strcmp(u->nome, a->usuario->nome) < 0)
        return a->esq = insere(a->esq, u);
    if(strcmp(u->nome, a->usuario->nome) > 0)
        return a->dir = insere(a->dir, u);

    return a;
}

void usuario_insere (Sistema* sys, Usuario* u)
{
    sys->raiz = insere(sys->raiz, u);
}

void realiza_cadastro(Sistema* sys)
{
    printf("Digite seu nome: ");
    char* n = le_string();
    printf("Digite seu login: ");
    char* l = le_string();
    printf("Digite sua senha: ");
    char* s = le_string();
    printf("Digite seu CPF: ");
    int i;
    scanf("%d", &i);
    printf("Qual seu perfil?\nDigite (1) para aluno e (2) para professor: ");
    int p;
    scanf("%d", &p);
    Usuario* u = usu_cria(n, p, i, l, s);
    usuario_insere(sys, u);
}
