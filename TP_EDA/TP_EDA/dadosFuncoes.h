/**

	@file      dadosFuncoes.h
	@brief     Estruturas e assinatura das Fun��es desenvolvidas para gest�o de m�quinas, opera��es e jobs.
	@author    Adriana Gomes
	@email	   a23151@alunos.ipca.pt
	@date      Abril de 2022

**/

#ifndef DADOS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

#define N 5


/**
    @struct Job
    @brief  Informa��o de um Job (C�digo do job, apontador para lista de opera��es e apontadores para arvore de jobs)
**/
typedef struct Job {
	int codigoJob;
	struct Operacao* listaOperacoes;
	struct Job* left;
	struct Job* right;
} Job;

/**
    @struct Operacao
    @brief  Informa��o de uma opera��o (C�digo, apontadores para lista de m�quina e para a pr�xima opera��o)
**/
typedef struct Operacao {
	int codigo;
	struct Maquina* listaMaquinas;
	struct Operacao* next;
} Operacao;

/**
    @struct Maquina
    @brief  Informa��o de uma m�quina (ID, tempo, apontador para a pr�xima m�quina)
**/
typedef struct Maquina {
	char id[N];
	int tempo;
	struct Maquina* next;
} Maquina;

/**
    @struct JobInfoFile
    @brief  Informa��o de um Job para armazenar num ficheiro
**/
typedef struct JobInfoFile {
	int codigoJob;
	Operacao operacaoFile;
	Maquina maquinaFile;
} JobInfoFile;

//-----------


/** 
	Assinaturas das fun��es desenvolvidas
*/
Job* iniciarArvore();
Job* lerFicheiroTexto();
Job* criarNodoJob(int codigoJob);
Job* inserirNodoJobArvore(Job* root, Job* novoJob);
Job* existeJob(Job* root, int codigoJob);
Job* removerJob(Job* root, int codigoJob);
Job* procurarMin(Job* root);
void mostrarArvore(Job* root);

void guardarArvore(Job* root, FILE* fp);
bool guardarArvoreFicheiro(Job* root, char* fileName);


Operacao* criarOperacao(int codigo);
Operacao* inserirOperacao(Operacao* h, Operacao* nova);
Operacao* removerListaOperacoes(Operacao* h);
Operacao* removerOperacao(Operacao* h, int codigo);
Operacao* existeOperacaoPtr(Operacao* h, int codigo);
bool existeOperacao(Operacao* h, int codigo);
void mostrarListaOperacao(Operacao* h);
void mostrarListaOperacaoeMaquinas(Operacao* h);


Operacao* inserirMaquinaOperacao(Operacao* h, int codOper, Maquina* m);
Maquina* criarMaquina(char* id, int tempo);
Maquina* inserirMaquina(Maquina* h, Maquina* nova);
Maquina* removerListaMaquinas(Maquina* h);
bool existeMaquina(Maquina* h, int idMaquina);

void tempoMinimo(Operacao* h);
void tempoMaximo(Operacao* h);
void tempoMedio(Operacao* h);

#define DADOS
#endif