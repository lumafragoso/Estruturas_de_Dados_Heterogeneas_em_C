#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFININDO REGISTRO PARA GUARDAR OS DADOS DOS TIMES
typedef struct time{
    char* str;
    int capacity, length;
} string;

void set_str(string *text, char* array){
    
    //ALOCAR INICIALMENTE A MEMÓRIA
    text->str =malloc(sizeof(char*) *16);

    //COPIAR O TEXTO DO ARRAY PARA O REGISTRO
    strcpy(text->str, array);
     
}

void read_str(string *nome){

    //ALOCAR PRIMEIRAMENTE A STRING
    nome->str =malloc(sizeof(char*) *16);

    //LER O NOME DADO
    fgets(nome->str, 301, stdin);

    //REALOCAR PARA AJUSTAR O TAMANHO DE ACORDO COM A LEITURA DOS DADOS
    nome->str = realloc(nome->str, sizeof(char*) *((strlen(nome->str)/16)+1) *16);

    //TIRAR O \n DO TEXTO
    nome->str = strtok(nome->str, "\n");

    //ADICIONAR O \0 PARA NOSSA STRING
    strcat(nome->str, "\0");

}

void concat_str(string *g, string *n){

    //SOMAR O TAMANHO DAS DUAS STRINGS, PARA DAR O TAMANHO DA STRING CONCATENADA
    g->length= strlen(n->str) + strlen(g->str);

    //CALCULAR A QUANTIDADE DE MEMORIA NECESSARIA
    g->capacity =((g->length/16)+1) *16;

    //REALOCAR A STRING DE ACORDO COM O TAMANHIO NECESSARIO
    g->str = realloc(g->str, sizeof(char*) *g->capacity);

    //CONCATENAR A STRING
    strcat(g->str, n->str);
    
}

void clear_str(string *vetor){

    //LIBERAR A MEMÓRIA ALOCADA
    free(vetor->str);
}

int main() {
    string greeting;
    string name;
    set_str(&greeting, "Oi ");
    read_str(&name);
    concat_str(&greeting, &name);
    printf("%s\n", greeting.str);
    printf("%i %i\n", greeting.capacity, greeting.length);
    clear_str(&greeting);
    clear_str(&name);
    return 0;
}