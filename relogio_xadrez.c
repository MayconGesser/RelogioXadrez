#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES_EXIBIDOS 5

struct TempoJogador {
	int minutos;
	int segundos;
	char *string_tempo; 
};

struct Relogio {
	int tempo_jogo; 
	int incremento;
	struct TempoJogador jogador_brancas; 
	struct TempoJogador jogador_pretas;  
};

void *initString(int minutos)
{
	char *str = (char *)malloc(sizeof(char)*CARACTERES_EXIBIDOS);
	sprintf(str,"0%d:00",minutos);
	return str;		
}

struct Relogio initRelogio(int tempo_jogo, int incremento)
{
	struct Relogio relogio;
	relogio.tempo_jogo = tempo_jogo; 
	relogio.incremento = incremento; 
	struct TempoJogador brancas; 
	struct TempoJogador pretas;
	brancas.minutos = relogio.tempo_jogo;
	brancas.segundos = 0;
	brancas.string_tempo = initString(brancas.minutos);
	pretas.minutos = relogio.tempo_jogo;
	pretas.segundos = 0;
	pretas.string_tempo = initString(pretas.minutos);
	relogio.jogador_brancas = brancas; 
	relogio.jogador_pretas = pretas;
	return relogio;
}

int main(void)
{
	struct Relogio relogio; 
	relogio = initRelogio(3,0);
	printf("%s\n",relogio.jogador_brancas.string_tempo);
	printf("%s\n",relogio.jogador_pretas.string_tempo);
	return 0;
}