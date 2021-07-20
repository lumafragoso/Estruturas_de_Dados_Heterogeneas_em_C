#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Enumeração representando itens do jogo

enum item{
  cura = 1,
  dinheiro,
  vigor  // escudo
};

//Enumeração representando as armadilhas
enum trap{
  buraco = 1,
  espinhos,
  ladrao
};

//Tipo Personagem, contendo vida e ataque. Usado para definir os inimigos e parte do Jogador
typedef struct person{
  int life;
  int attack;
} Personagem;

//Tipo Jogador. Contém um Personagem com informações de vida e ataque, além de uma posição x,y e informações de dinheiro (loot) e se está equipado com escudo ou não.
typedef struct player{
  Personagem p; 

  int x, y, escudo, loot;
}Jogador;

//Tipo de dado Sala, representa uma casa do mapa. Pode conter um personagem inimigo, um tesouro e/ou uma armadilha
typedef struct room{
  Personagem p;
  int tesouro;
  int armadilha;
} Sala;

void inicializar(int L, int C, Jogador* play, Sala** map){
	int i, j;

	//INICIALIZAR ESCUTO E LOOT COMO ZERO
	play->escudo = 0;
 	play->loot = 0;

	//INICIALIZAR NAS POSIÇÕES DO MAPA A VIDA, ATAQUE, TESOURO E ARMADILHA COMO ZERO
	for(i=0;i<L; i++){
		for(j=0; j<C; j++){
      	map[i][j].p.life = 0;
      	map[i][j].p.attack = 0;
      	map[i][j].tesouro = 0;
      	map[i][j].armadilha = 0;
		}
	}
}

void inimigo_itens(int inimigo, int tesou, int arma, Sala** tab, Jogador* player){
	int i, j, k;
	int l, c, vida, ataque;
	char tesouro[35], armadilha[35];

	//INIMIGO
	for (i = 0; i < inimigo; ++i){
		//LÊ A ENTRADA DO INIMIGO
		scanf("(%d %d) - %d %d\n", &l, &c, &vida, &ataque);
		//PARA SE ADEQUAR AOS TAMANHOS DA MATRIZ 0-9
        l--;
        c--;
		tab[l][c].p.life = vida;
		tab[l][c].p.attack = ataque;
	}

	//TESOURO
	for (j=0; j<tesou ;j++){
		scanf("%s %i %i\n", tesouro, &l, &c);
		//PARA SE ADEQUAR AOS TAMANHOS DA MATRIZ 0-9
        l--;
        c--;
		
		if (strcmp(tesouro,"cura")==0){
			tab[l][c].tesouro = 1;
		}
		else if (strcmp(tesouro,"dinheiro")==0){
			tab[l][c].tesouro = 2;
		}		
		else if (strcmp(tesouro,"escudo")==0){
			tab[l][c].tesouro = 3;
		}
    }

	//ARMADILHA
	for (k=0; k<arma; k++){
		scanf("%s %i %i\n", armadilha, &l, &c);
		//PARA SE ADEQUAR AOS TAMANHOS DA MATRIZ 0-9
        l--;
        c--;
		//BURACO PERDE 10 DE VIDA
		if (strcmp(armadilha,"buraco")==0){
			tab[l][c].armadilha = 1;
		}
		//ESPINHO PERDE 5 DE VIDA
		else if (strcmp(armadilha,"espinhos")==0){
			tab[l][c].armadilha = 2;
		}	
		//LADRAO PERDE DINHEIRO	
		else if (strcmp(armadilha,"ladrao")==0){
			tab[l][c].armadilha = 3;
		}		
	}
}

Sala** cria_mapa(int lin, int col, Jogador* player){
	int I, T, A, l, c, i, j, k;
	Sala **mapa;
	mapa = malloc(sizeof(Sala *) * lin);

	//ALOCAÇÃO DAS COLUNAS
  	for(i=0; i<lin; i++){
    	mapa[i] = malloc(sizeof(Sala) * col);
  	}
	
	//INICIALIZAR OS VALORES COMO ZERO
	inicializar(lin, col, player, mapa);

  	//LÊ A ENTRADA DO JOGADOR
	scanf(" (%i %i) - %i %i\n", &(player->x), &(player->y), &(player->p.life), &(player->p.attack));

  	//LÊ INIMIGOS TESOUROS E ARMADILHA
	scanf("%d %d %d\n", &I, &T, &A);

	//FUNÇÃO PARA LER INIMIGO, ITENS E ARMADILHA
	inimigo_itens(I, T, A, mapa, player);

	printf("Mapa inicializado!\n");
    printf("Jogador na posicao %i,%i\n", (player->x),(player->y));

	//DIMINUIR 1, POIS A DIMENSÃO DO MAPA VAI DE 0-9
    (player->x)= (player->x) -1 ;
    (player->y)= (player->y) - 1;

  	return mapa;
}

void tesouro(int X, int Y, Sala** m,Jogador* P){
	if (m[X][Y].tesouro != 0){
		printf("Um tesouro!\n");

		//CURA
		if(m[X][Y].tesouro == 1){
			printf("Jogador coleta: pocao de cura!\n");
			P->p.life += 10;
		}
		//DINHEIRO
		else if(m[X][Y].tesouro == 2){
			printf("Jogador coleta: dinheiro!\n");
			P->loot += 10;				
		}
		//ESCUDO
		else{
			printf("Jogador coleta: um escudo!\n");
			P->escudo += 1;
		}
	}
}

void armadilha(int X, int Y, Sala** m,Jogador* P){
	//BURACO
	if(m[X][Y].armadilha == 1){
		printf("Armadilha: buraco! Jogador se machuca!\n");
		P->p.life -= 10;
	}
	//ESPINHO
	else if(m[X][Y].armadilha == 2){
		printf("Armadilha: espinhos! Jogador se machuca!\n");
		P->p.life -= 5;
	}
	//LADRAO
	else{
		printf("Armadilha: ladrao! Jogador perde dinheiro!\n");
		if (P->loot<=10){
			P->loot = 0;
		}
		else{
			P->loot -= 10;
		}
	}
}

int ataque(int X, int Y, Sala** m,Jogador* P){
	//JOGADOR ATACA
	printf("Jogador ataca!\n");

	//DIMINUIR A VIDA DO INIMIGO
	m[X][Y].p.life -= P->p.attack;

	//PRINTAR DANO
    printf("Dano de %i\n", P->p.attack);

	//CASO A VIDA DO INIMIGO SEJA ZERO
	if(m[X][Y].p.life <= 0){
		printf("Vida do inimigo: 0\n");
	}
	//CASO A VIDA DO INIMIGO NÃO SEJA ZERO
	else{
		printf("Vida do inimigo: %i\n", m[X][Y].p.life);
	}
	//CASO A VIDA SEJA ZERO, RETORNA 1 PARA DAR BREAK
	if(m[X][Y].p.life <= 0){
		return 1;
	}

	//INIMIGO ATACA
	//SE NÃO TIVER ESCUDO ATACA DIRETAMENTE AO JOGADOR
	if(P->escudo == 0){
		printf("Inimigo ataca!\n");

		//DIMINUIR A VIDA DO JOGADOR
		P->p.life -= m[X][Y].p.attack;

		//PRINTAR DANO
		printf("Dano de %i\n", m[X][Y].p.attack);

		//CASO A VIDA DO JOGADOR SEJA ZERO
		if(P->p.life<=0){
			printf("Vida do jogador: 0\n");
		}
		//CASO A VIDA DO JOGADOR NÃO SEJA ZERO
		else{
			printf("Vida do jogador: %i\n", P->p.life);
		}
	}
	//SE TIVER ESCUDO, ATACA NO ESCUDO
	else{
        P->escudo = 0;
		printf("Defendeu o golpe!\n");
	}
}


int executa_passo(int N, int M, Sala** mapa, char step, Jogador* p){
	int x, y, control=1, retorno=1;

	//CASO CIMA
	if(step == 'W'){
		x = p->x - 1;
		y = p->y;
	}
	//CASO ESQUERDA
	else if(step == 'A'){
		x = p->x;
		y = p->y - 1;
	}
	//CASO BAIXO
	else if(step == 'S'){
		x = p->x + 1;
		y = p->y;
	}
	//CASO DIREITA
	else if(step == 'D'){
		x = p->x;
		y = p->y + 1;
	}

	printf("Avancando para %i, %i...\n", x+1,y+1);


	//CASO O MOVIMENTO SEJA ILEGAL
	if (x>=N || y>=M || x<0 || y<0){
		printf("Movimento Ilegal!\n");
	}
	else{
		//ATUALIZAR VALORES
		p->x = x;
		p->y = y;

		//INIMIGO
		if (mapa[x][y].p.life != 0){
			printf("Um inimigo!!!\n");

			do{
				//CHAMA A FUNÇÃO DE ATAQUE
				if(ataque(x, y, mapa, p)== 1){
					break;
				}
				//CASO A VIDA DO PERSONAGEM SEJA ZERO
				if(p->p.life <= 0){
					return -1;
				}
			}while(control);
		}

		//ARMADILHA
		if (mapa[x][y].armadilha != 0){

			//CHAMA A FUNÇÃO ARMADILHA
			armadilha(x, y, mapa,p);

			//CASO A VIDA DO PERSONAGEM SEJA ZERO
			if(p->p.life <= 0){
				return -1;
			}
		}

		//TESOURO
		//CHAMA A FUNÇÃO TESOURO
		tesouro(x, y, mapa, p);
	}

	return 1;
}

void imprime_status_personagem(Jogador p){
	printf("Terminou na posicao (%i, %i)\n", (p.x)+1, (p.y)+1);
	printf("Vida: %i\n", p.p.life);
	printf("Dinheiro: %i", p.loot);
}


//Função principal

int main(){
  int n, m, movimentos, res, i;
  char passo;
  Jogador player;
  Sala** mapa;

  //Leitura do tamanho do mapa
  scanf("%d %d", &n, &m);

  //Função que cria o mapa e inicializa o Jogador de acordo com os dados da entrada
  mapa = cria_mapa(n, m, &player);

  //Leitura dos movimentos da simulação
  scanf("%d", &movimentos);

  //Para cada movimento do jogador...
  for(i=0; i<movimentos; i++){
    //Lê o movimento
    scanf(" %c", &passo);

    //Executa a simulação do passo. Se o retorno for -1, o jogador morreu e encerra a simulação
    res = executa_passo(n, m, mapa, passo, &player);
    if(res == -1) break;
  }
 
  //Testa pra ver se o jogador terminou vivo
  res < 0 ? printf("You died...\n"): printf("Vitoria!\n");

  //Imprime as informações finais do jogador
  imprime_status_personagem(player);

  return 0;
}