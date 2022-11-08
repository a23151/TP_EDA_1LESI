/**

    @file      Funcoes1.c
    @brief     Funcoes desenvolvidas para uma proposta de escalonamento.
    @author    Adriana Gomes
    @email	   a23151@alunos.ipca.pt
    @date      Maio de 2022

**/

#pragma warning( disable : 4996 )

#include "dadosFuncoes.h"
#include "dadosEscalonamento.h"


/**
	@brief	Inicializar o array bidimensional
	@param plano - array bidimensional com maquinas (linhas) e unidades de tempo (colunas)
 **/
void iniciaPlano(Planeamento plano [][T]) {

	for (int l = 0; l < M; l++) {
		for (int c = 0; c < T; c++) {
			plano[l][c].codigoJob = valorIni;
			plano[l][c].codigoOper = valorIni;
		}
	}
}

/**
	@brief	Inicializar o array auxiliar
	@param plano	Array que armazena a informação de todas as operações de cada job
 **/
void iniciarArrayAuxiliar(Celula auxiliar[]) {
	int i;
	for (i = 0; i < T; i++) {
		auxiliar[i].codigoJob = valorIni;
		auxiliar[i].codigoOper = valorIni;
		strcpy(auxiliar[i].idMaq, "-1");
		auxiliar[i].tempo = valorIni;
		auxiliar[i].tempoFinal = valorIni;
	}
}


/**
   @brief	Para cada nodo da árvore preenche a estrutura Celula (auxCel). Esta informação é colocada um array auxiliar através da função preencheArrayAuxiliar.
   @param root 
 */
void preencherCelula(Job* root, Celula auxiliar []) {
	int tempoMinimo;
	int maq;
	Celula auxCel;
	

	auxCel.codigoJob = root->codigoJob;

	Operacao* auxOper = root->listaOperacoes;
	while (auxOper) {

		auxCel.codigoOper = auxOper->codigo;

		Maquina* auxMaq = auxOper->listaMaquinas;
		tempoMinimo = auxMaq->tempo;
		strcpy(auxCel.idMaq, auxMaq->id);			//porque as máquinas podem demorar o mesmo tempo (e não entra no if)

		while (auxMaq) {

			if (auxMaq->tempo < tempoMinimo) {
				tempoMinimo = auxMaq->tempo;
				strcpy(auxCel.idMaq, auxMaq->id);
			}
			auxMaq = auxMaq->next;
		}
		auxCel.tempo = tempoMinimo;

		preencheArrayAuxiliar(auxiliar, &auxCel);

		auxOper = auxOper->next;
	}
}


/**
   @brief Preencher array auxiliar
   param auxiliar	array
   param nova Celula com informação da máquina mais rápida de cada operação do job
**/
void preencheArrayAuxiliar(Celula auxiliar[], Celula* nova) {
	int i=0;
			
		while (auxiliar[i].codigoJob != valorIni)
			i++;

		auxiliar[i].codigoJob = nova->codigoJob;
		auxiliar[i].codigoOper = nova->codigoOper;
		strcpy(auxiliar[i].idMaq, nova->idMaq);
		auxiliar[i].tempo = nova->tempo;
		auxiliar[i].tempoFinal = valorIni;
	}


/**
	@brief	 Função que permite preencher a célula com a informação da máquina mais rápida para uma determinada operação de um job.
	@param root		Árvore de jobs
	@return		Célula preenchida
 **/
void preencherArrayArvore (Job* root, Celula auxiliar[]) {

	if (root == NULL) return;

	preencherArrayArvore(root->left, auxiliar);

	preencherCelula(root, auxiliar);

	preencherArrayArvore(root->right, auxiliar);
}



/**
	@brief	Função que associa o ID da máquina a um valor inteiro 
	@param nova		Célula com novos dados
	@return		ID da máquina
 **/
int devolveMaquina(Celula nova) {
	int maq;
	maq = (int)nova.idMaq[1]-48;
	return maq;
}


/**
	@brief	Preenche o plano
	@param plano	Array bidimensional para representar o escalonamento
	@param auxiliar		Array auxiliar com a informação de cada operação
 **/
void ocupaPlano(Planeamento plano[][T], Celula auxiliar[]) {
	int i = 0;
	int maqId;
	int col = 0;
	int colIni;
	int tempoTotal;
	bool celulaLivre = false;

	for (i = 0; i < T; i++) {

		if (auxiliar[i].codigoJob == valorIni) return;

		if (i == 0 || auxiliar[i].codigoJob != auxiliar[i-1].codigoJob) {	//jobs começam em t=0 (se maquina livre)
			col = 0;
		}
		else {
			col = auxiliar[i - 1].tempoFinal;
		}

		maqId = devolveMaquina(auxiliar[i]);

		while (plano[maqId][col].codigoJob != valorIni)		//procurar a primeira "posição" livre
			col++;

		tempoTotal = auxiliar[i].tempo + col;					 //para preencher as células seguintes à col encontrada
		celulaLivre = false;

		while ((col < T && celulaLivre == false))		//confirmar se tem o nº de celulas necessárias livres 
		{
			colIni = col;
			for (; col < tempoTotal; col++) {
				if (plano[maqId][col].codigoJob != valorIni)
				{
					celulaLivre = false;
					col++;
					break;
				}
			}
			if (col == tempoTotal)
				celulaLivre = true;
		}

		if (celulaLivre) {

			for (; colIni < tempoTotal; colIni++) {
				plano[maqId][colIni].codigoJob = auxiliar[i].codigoJob;
				plano[maqId][colIni].codigoOper = auxiliar[i].codigoOper;
			}

		}
		auxiliar[i].tempoFinal = colIni;		 //indica onde pode começar a próxima operação
	}
}



/**
	@brief	Exporta dados do plano para um ficheiro csv
    @param plano	Array Escalonamento
 */
void exportarPlanoCsv(Planeamento plano[][T]) {
	FILE* fp;
	int maqId;
	int col;
	int inicio = 0;
	int fim = 0;

	fp = fopen("dados.csv", "w+");
	if (fp == NULL) 
		return NULL;

	for (maqId = 1; maqId <= 9; maqId++) {

		for (col = 0; col < T; col++) {

			if (plano[maqId][col].codigoJob != valorIni) {
				inicio = col;
				while (plano[maqId][col].codigoJob == plano[maqId][col+1].codigoJob) {
					col++;
				}
				//printf("maquina %d job %d, operation %d,%d,%d\n", maqId, plano[maqId][col].codigoJob, plano[maqId][col].codigoOper, inicio, col);
				fprintf(fp, "maquina %d,Job %d Operation %d,%d,%d\n", maqId, plano[maqId][col].codigoJob, plano[maqId][col].codigoOper, inicio, col);
			}
		}
	}
	fclose(fp);
}


//void mostraPlano(Planeamento plano[][T]) {
//	int i, j;
//
//	for (i = 0; i < 10; i++) {
//		for (j = 0; j < 10; j++) {
//
//			printf("Job: %d, Oper: %d\t", plano[i][j].codigoJob, plano[i][j].codigoOper);
//		}
//	}
//}
