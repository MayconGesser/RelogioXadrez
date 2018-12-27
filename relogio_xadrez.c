#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define CARACTERES_EXIBIDOS 5

int bit_jogador_vez = 1;
int jogo_em_andamento = 1;
pthread_mutex_t trava;
pthread_t tid; 

struct TempoJogador {
	int minutos;
	int segundos;
	int incremento;
	char *string_tempo;
	int bt_foi_press;  
};

struct Relogio {
	int tempo_jogo; 
	struct TempoJogador jogador_brancas; 
	struct TempoJogador jogador_pretas;
};

void rt_input(struct TempoJogador tempo_jogador)
{
	while(!tempo_jogador.bt_foi_press)
	{
		if(getchar() == "\n")
		{
			tempo_jogador.segundos += tempo_jogador.incremento;
			tempo_jogador.bt_foi_press = 1;
		}
	}
}

void *init_string(int minutos, int segundos)
{
	char *str = (char *)malloc(sizeof(char)*CARACTERES_EXIBIDOS);
	sprintf(str,"0%d:%s%d",minutos,segundos);
	return str;		
}

struct Relogio init_relogio(int tempo_jogo, int incremento)
{
	struct Relogio relogio;
	relogio.tempo_jogo = tempo_jogo; 
	struct TempoJogador brancas; 
	struct TempoJogador pretas;
	brancas.minutos = relogio.tempo_jogo;
	brancas.segundos = 0;
	brancas.incremento = incremento;
	brancas.string_tempo = init_string(brancas.minutos, brancas.segundos);
	pretas.minutos = relogio.tempo_jogo;
	pretas.segundos = 0;
	pretas.incremento = incremento;
	pretas.string_tempo = init_string(pretas.minutos, pretas.segundos);
	relogio.jogador_brancas = brancas; 
	relogio.jogador_pretas = pretas;
	return relogio;
}

int acabou_tempo(struct TempoJogador tempo_jogador)
{
	return tempo_jogador.minutos == 0 && tempo_jogador.segundos == 0; 
}

void atualizar_e_imprimir_string_tempo(struct TempoJogador tempo_jogador)
{
}

int comecar_jogo(struct Relogio relogio)
{
	struct TempoJogador jogador_brancas, jogador_pretas, jogador_da_vez;
	jogador_brancas = relogio.jogador_brancas;
	jogador_pretas = relogio.jogador_pretas;
	while(!acabou_tempo(jogador_brancas) || !acabou_tempo(jogador_pretas))
	{
		jogador_da_vez = (bit_jogador_vez & 1 ? jogador_brancas : jogador_pretas); //jogadas impares sao pecas brancas, pares sao pretas
		pthread_create(&tid, NULL, &rt_input, NULL);
		while(!jogador_da_vez.bt_foi_press)						
		{
			sleep(1);
			if(jogador_da_vez.segundos == 0)
			{
				jogador_da_vez.segundos = 59; 
				jogador_da_vez.minutos -= 1;
			}
			else 
			{
				jogador_da_vez.segundos -= 1;	
			}
			atualizar_e_imprimir_string_tempo(jogador_da_vez);
		}
		pthread_join(tid, NULL);
		bit_jogador_vez++;
	}
	jogo_em_andamento = 0; 
}

int main(void)
{
	struct Relogio relogio; 
	relogio = init_relogio(3,0);
	printf("%s\n",relogio.jogador_brancas.string_tempo);
	printf("%s\n",relogio.jogador_pretas.string_tempo);
	return 0;
}