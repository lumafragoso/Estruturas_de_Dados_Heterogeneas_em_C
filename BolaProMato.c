#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFININDO REGISTRO PARA GUARDAR OS DADOS DOS TIMES
typedef struct time{
    char nome[201];
    int vitorias, empates, derrotas, gols_feitos, gols_sofridos;
} Entrada;

void impressao(int point[], int t, Entrada* vetor){
    int i=0, j=0, k=0;

    printf("Tabela do campeonato:\nNome| Pontos| Jogos| Vitorias| Empates| Derrotas| Gols Pro| Gols Contra| Saldo de Gols\n");

    for (i = 0; i < t; i++){
        printf("%s| %d| %d| %d| %d| %d| %d| %d| %d\n", vetor[i].nome, 3*vetor[i].vitorias + vetor[i].empates, (vetor[i].vitorias+vetor[i].empates+vetor[i].derrotas), vetor[i].vitorias, vetor[i].empates, 
        vetor[i].derrotas, vetor[i].gols_feitos, vetor[i].gols_sofridos, vetor[i].gols_feitos - vetor[i].gols_sofridos);
    }

    printf("\n");
    printf("Times na zona da libertadores:\n");

    for (j = 0; j < 6; j++){
        printf("%s\n", vetor[j].nome);
    }

    printf("\n");
    printf("Times rebaixados:\n");

    for (k = t-1; k > t-5; k--){
        printf("%s\n", vetor[k].nome);
    }
    
    
    
}

void ordena_campeonato(Entrada* vet, int tam){
    int i=0, j=0;
    int pontos[tam];
    Entrada aux;

    //LOOP PARA VERIFICAR CADA POSIÇÃO, NÃO É NECESSÁRIO VERIFICAR A ÚLTIMA
    for(i=0; i<tam-1; i++){
        //COLOCAR EM UM VETOR Q QUANTIDADE DE PONTOS DE CADA TIME
        
        
        //CADA POSIÇÃO COM TODO O RESTO DO VETOR
        for(j= i+1; j<tam; j++){
            //PONTOS
            if(3*vet[i].vitorias + vet[i].empates< (3*vet[j].vitorias + vet[j].empates)){
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
            //NÚMERO DE VITÓRIAS
            else if(3*vet[i].vitorias + vet[i].empates== (3*vet[j].vitorias + vet[j].empates) && vet[i].vitorias < vet[j].vitorias){
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
            //SALDO DE GOLS
            else if(vet[i].vitorias == vet[j].vitorias && vet[i].gols_feitos - vet[i].gols_sofridos< vet[j].gols_feitos-vet[j].gols_sofridos){
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
    pontos[tam-1]= 3*vet[tam-1].vitorias + vet[tam-1].empates;
    impressao(pontos, tam, vet);

}
Entrada separa(char* string, int j){
    Entrada aux;
    char* parte;

    parte = strtok(string, ";");

    //aux.nome[j] = malloc(sizeof(char) * strlen(parte) + 1);
    strcpy(aux.nome, parte);

    parte = strtok(NULL, "\n");
    sscanf(parte, " %d %d %d %d %d", &aux.vitorias, &aux.empates, &aux.derrotas, &aux.gols_feitos, &aux.gols_sofridos);

    return aux;
}


void leitura(int n){
    int i=0;
    char texto[201];
    Entrada camp[n];

    //LER TODOS OS DADOS DOS TIMES
    for(i=0; i<n; i++){
        scanf(" %[^\n] ", texto);
        camp[i] = separa(texto, i);

    }

    //FUNÇÃO COM BUBBLESORT PARA ORDENAR OS TIMES
    ordena_campeonato(camp, n);
}

int main(){
    int quantidade;

    //LEITURA DA ENTRADA
    scanf(" %d", &quantidade);

    leitura(quantidade);
    return 0;
}