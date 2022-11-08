/**

	@file      dadosEscalonamento.h
	@brief     Funções desenvolvidas para uma proposta de escalonamento.
	@author    Adriana Gomes 
	@email	   a23151@alunos.ipca.pt
	@date      Abril de 2022

**/

#include "dadosFuncoes.h"

#define M 8
#define T 20
#define valorIni -1

/**
	@struct Celula
	@brief  Informação sobre o tempo que uma máquina precisa para realizar uma determinada operação
 */
typedef struct Celula {
	int codigoJob;
	int codigoOper;
	char idMaq [N];
	int tempo;
	int tempoFinal;
} Celula;


typedef struct Planeamento {
	int codigoJob;
	int codigoOper;
} Planeamento;


/**
	Assinaturas das funções desenvolvidas para o escalonamento
*/

void iniciaPlano(Celula plano[][T]);
void iniciarArrayAuxiliar(Celula auxiliar[]);
int devolveMaquina(Celula* nova);
void preencherCelula(Job* root, Celula auxiliar[]);
void preencherArrayArvore(Job* root, Celula auxiliar[]);
void preencheArrayAuxiliar(Celula auxiliar[], Celula* nova);
void ocupaPlano(Planeamento plano[][T], Celula auxiliar[]);
void exportarPlanoCsv(Planeamento plano[][T]);
//void mostraPlano(Planeamento plano[][T]);

