/**

    @file      Funcoes1.c
    @brief     Funcoes desenvolvidas para gestao de jobs. Os jobs estão organizados numa estrutura de ABP.
    @author    Adriana Gomes
    @email	   a23151@alunos.ipca.pt
    @date      Maio de 2022

**/

#pragma warning( disable : 4996 )

#include "dadosFuncoes.h"

#pragma region Job

/**
    @brief  Inicia a arvore
    @return  - NULL 
**/
Job* iniciarArvore() {
    return NULL;
}


/**
    @brief  Ler ficheiro de texto e construir a arvore, com os operacoes e as maquinas
    @return  - Árvore de Jobs
**/
Job* lerFicheiroTexto() {
	int job, operacao, tempo;
	char maquina[N];

	Job* novoJob = NULL;

	Job* arvore = NULL;

	FILE* fp;
	fp = fopen("dadosIniciais.txt", "rt");
	if (fp == NULL) return NULL;


	while (!feof(fp)) {

		fscanf(fp, "%d; %d; %d; %s;\n", &job, &operacao, &tempo, maquina);

		//printf("%d; %d; %s; %d\n", job, operacao, maquina, tempo);


		//Se job nao existe, cria e insere!
		if (existeJob(arvore, job) == NULL)	//Verificação
		{
			//printf("NAO EXISTE: Novo Job: %d\n", job);
			novoJob = criarNodoJob(job);
			arvore = inserirNodoJobArvore(arvore, novoJob);
			//printf("Depois - Novo Job: %d\n", job);
		}

		//procurar nas operaçoes do job a operacao a tratar
		Operacao* auxOper = existeOperacaoPtr(novoJob->listaOperacoes, operacao);
		//se a operacao a tratar não exste, criar e inserir
		if (auxOper == NULL) {
			Operacao* novaOper = criarOperacao(operacao);
			novoJob->listaOperacoes = inserirOperacao(novoJob->listaOperacoes, novaOper);
		}

		if (auxOper == NULL)
			auxOper = existeOperacaoPtr(novoJob->listaOperacoes, operacao);

		if (existeMaquina(auxOper->listaMaquinas, maquina) == false) {

			Maquina* novaMaquina = criarMaquina(maquina, tempo);
			auxOper->listaMaquinas = inserirMaquina(auxOper->listaMaquinas, novaMaquina);
			//novoJob->listaOperacoes = inserirMaquinaOperacao(novoJob->listaOperacoes, operacao, novaMaquina);
		}

		//printf("%d", novoJob->codigoJob);
	}
	fclose(fp);
	return arvore;
}


/**
    @brief  Cria novo Job
    @param  codigoJob - Código no novo Job
    @return           - novo Job
**/
Job* criarNodoJob(int codigoJob) {

	Job* novoJob = (Job*)malloc(sizeof(Job));
	if (novoJob == NULL) {
		return NULL;
	}
	novoJob->codigoJob = codigoJob;
	novoJob->listaOperacoes = NULL;
	novoJob->left = NULL;
	novoJob->right = NULL;

	return novoJob;
}


/**
    @brief  Constrói (insere nodos) a árvore binária. Se o código do novo Job é maior do que a raiz, insere do lado direito, se for menor é inserido do lado esquerdo. 
    @param  root    - Raiz da árvore (início)
    @param  novoJob - Job a ser inserido
    @return         - Apontador para a raiz da árvore
**/
Job* inserirNodoJobArvore(Job* root, Job* novoJob) {

	if (root == NULL) {
		root = novoJob;
	}  
	else {
		if (root->codigoJob > novoJob->codigoJob) {
			root->left = inserirNodoJobArvore(root->left, novoJob);
		}
		else
			if (root->codigoJob < novoJob->codigoJob)
				root->right = inserirNodoJobArvore(root->right, novoJob);
	}
	return root;
}

/**
    @brief Mostra o código dos Jobs (nodos) da árvore in-order.
    @param root - Raiz da árvore
**/
void mostrarArvore(Job* root) {
	if (root == NULL) return;
	mostrarArvore(root->left);
	printf("Root: %d \n", root->codigoJob);
	mostrarArvore(root->right);
}

/**
    @brief  Verifica se o Job existe na árvore. Compara os códigos dos Jobs. 
    @param  root      - Raiz da árvore
    @param  codigoJob - Código do Job
    @return           - Devolve a árvore caso o Job exista ou NULL se não existir
**/
Job* existeJob(Job* root, int codigoJob) {
	if (root == NULL)
		return NULL;
	if (root->codigoJob == codigoJob)
		return root;

	if (root->codigoJob > codigoJob) {
		return(existeJob(root->left, codigoJob));
		//root->left = existeJob(root->left, codigoJob);
	}
	else
		if (root->codigoJob < codigoJob) {
			return(existeJob(root->right, codigoJob));
		}
	//return root;
}

/**
    @brief  Remove um Job da árvore. Percorre a árvore e se o nodo tiver um "filho", será guardada numa váriavel temporária
	e depois inserida na árvore. Caso o nodo tenha dois "filhos", é substituido pelo nodo mais à esquerda (menor) do seu nodo direito 
    @param  root      - Raíz da árvore
    @param  codigoJob - Código do Job a ser removido
    @return           - Árvore binária de Jobs
**/
Job* removerJob(Job* root, int codigoJob) {
	if (root == NULL) return NULL;

	if (codigoJob < root->codigoJob)
		root->left = removerJob(root->left, codigoJob);
	else
		if (codigoJob > root->codigoJob)
			root->right = removerJob(root->right, codigoJob);				//percorre a arvore
								
		else {												//root->codigoJob = codigoJob
							
			if (root->left == NULL) {
				Job* temp = root;
				root = root->right;
				removerListaOperacoes(temp->listaOperacoes);
				free(temp);
				return root;
			}
			else if (root->right == NULL) {
				Job* temp = root;
				root = root->left;
				removerListaOperacoes(temp->listaOperacoes);
				free(temp);
				return root;
			}
				
				Job* temp = procurarMin(root->right);
				root = temp;
				root->right = removerJob(root->right, temp->codigoJob);
		}
	return root;
}

/**
    @brief  Procura o mínimo do lado direito da árvore
    @param  root - Raíz da árvore
    @return      - Apontador para o nodo com o mínimo valor da árvore binária
**/
Job* procurarMin(Job* root) {
	if (root->left == NULL) return root;
	else
		return(procurarMin(root->left));
}

/**
    @brief  Guarda toda a informação da árvore (jobs, operações e máquinas).
    @param  root     - Raiz da árvore
    @param  fp - Apontador para o ficheiro 
**/
void guardarArvore(Job* root, FILE *fp) {

	JobInfoFile auxFile;
		
	if (root == NULL) return;

	//Grava a root corrente
	auxFile.codigoJob = root->codigoJob;
	Operacao* auxOper = root->listaOperacoes;
	while (auxOper) {
		auxFile.operacaoFile.codigo= auxOper->codigo;

		Maquina* auxMaq = auxOper->listaMaquinas;
		while (auxMaq) {
			auxFile.maquinaFile.tempo = auxMaq->tempo;
			strcpy(auxFile.maquinaFile.id, auxMaq->id);
			fwrite(&auxFile, sizeof(auxFile), 1, fp);
			auxMaq = auxMaq->next;
			} 
		auxOper = auxOper->next;
	}
	guardarArvore(root->left, fp);
	guardarArvore(root->right, fp);
}


/**
	@brief  Guarda toda a informação da árvore (jobs, operações e máquinas) num ficheiro.
	@param  root     - Raiz da árvore
	@param  fileName - Nome do ficheiro onde vai ser guardada a informação
	@return			 - True se abrir, guardar e fechar o ficheiro.
**/
bool guardarArvoreFicheiro(Job* root, char* fileName) {
	
	FILE* fp;

	if ((fp = fopen(fileName, "wb")) == NULL) return false;
	guardarArvore(root, fp);
	
	fclose(fp);
	return true;
}

#pragma endregion