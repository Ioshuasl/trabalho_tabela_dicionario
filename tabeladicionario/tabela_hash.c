#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10000000
#define N 127

struct aluno
{
    int mat;
    char nome[50];
    char email[100];
    char turma[2];
};

typedef struct aluno Aluno;
typedef Aluno* Hash[N];
Aluno vet[N];
static int hash(int mat);
Aluno* hsh_insere(Hash tab, int mat, char* n, char* e, char* t);    
Aluno* hsh_busca(Hash tab, int mat);
int inserirElemento(Hash tab);


static int hash(int mat)
{
    return (mat%N);
}

Aluno* hsh_busca(Hash tab, int mat)
{
    int h = hash(mat);
    while(tab[h] != NULL){
        if(tab[h]->mat == mat)
            return tab[h];
        h = (h+1) % N;
    }
    return NULL;
}

Aluno* hsh_insere(Hash tab, int mat, char* n, char* e, char* t)
{
    int h = hash(mat);
    while(tab[h] != NULL){
        if(tab[h]->mat == mat)
            break;
        h = (h+1)%N;
    }
    if(tab[h]==NULL){
        tab[h] = (Aluno*) malloc(sizeof(Aluno));
        tab[h]->mat =  mat;
    }
    strcpy(tab[h]->nome,n);
    strcpy(tab[h]->email,e);
    strcpy(tab[h]->turma,t);
    return tab[h];
}

int inserirElemento(Hash tab){
    Aluno* a;
    int  matricula;
    char  nome[50];
    char  email[100];
    char turma[2];
    printf("\nEntre com o número de matrícula do aluno: ");
    scanf("%d",&matricula);
    printf("\nEntre com o nome do aluno: ");
    scanf("%s",nome);
    printf("\nEntre com o e-mail do aluno: ");
    scanf("%s",email);
    printf("\nEntre com a turma do aluno: ");
    scanf("%s",turma);
    a = hsh_insere(tab,matricula,nome,email,turma);
    return matricula;
    
}

int main(){
    
    Aluno* b;
    Hash t;
    int chave, m, f;
    m = inserirElemento(t);
    printf("\nEntre com uma chave a ser procurada na tabela: ");
    scanf("%d",&chave);
    b =  hsh_busca(t,chave);
    if(b!=NULL)
        printf("\nA tabela hash na posição %d  está ocupada com o aluno: %s, email: %s, turma: %s \n",b->mat,b->nome,b->email,b->turma);   
    else
        printf("\nA posição procurada não está salva na tabela  hash\n");
    free(b);
    getchar();
    return 0;
}