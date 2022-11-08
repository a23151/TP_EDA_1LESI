/**

    @file      Funcoes1.c
    @brief     Funções desenvolvidas para a fase 1 do projeto, para gestão de operações e máquinas de um job.
    @author    Adriana Gomes
	@email	   a23151@alunos.ipca.pt	
    @date      Abril de 2022

**/

#pragma warning( disable : 4996 )

#include "dadosFuncoes.h"

#pragma region Operacoes
/**
    @brief  Cria uma operação
    @param  codigo - Código da operação
    @return        - Retorna a operação criada
**/
Operacao* criarOperacao(int codigo) {

	Operacao* novaOperacao = (Operacao*)malloc(sizeof(Operacao));
	if (novaOperacao == NULL) {		// verifica se foi alocada mem�ria
		return NULL;
	}
	novaOperacao->codigo = codigo;
	novaOperacao->next = NULL;
	novaOperacao->listaMaquinas = NULL;
	return novaOperacao;
}

/**
    @brief  Insere operações no final da lista
    @param  h    - Início da lista
    @param  nova - Nova operação a inserir
    @return      - Devolve início da lista
**/
Operacao* inserirOperacao(Operacao* h, Operacao* nova) {
	if (existeOperacao(h, nova->codigo)) return h;

	if (h == NULL) {	//se lista vazia, insere no inicio
		h = nova;
		return (h);
	}
	else
	{
		Operacao* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nova;
	}
	return h;
}

/**
    @brief Mostra a lista de operações
    @param h - Início da lista
**/
void mostrarListaOperacao(Operacao* h) {
	Operacao* aux = h;
	while (aux != NULL) {
		printf("Operacao %d; ", aux->codigo);
		aux = aux->next;
	} printf("\n");
}

/**
    @brief  Remove lista de operações. Remove primeiro as listas de máquinas associadas às operações.
    @param  h - Início da lista
    @return   - Devolve início da lista
**/
Operacao* removerListaOperacoes(Operacao* h) {
	Operacao* auxOp;

	auxOp = h;
	while (auxOp != NULL) {
		h = auxOp->next;
		removerListaMaquinas(auxOp->listaMaquinas);
		free(auxOp);
		auxOp = h;
	}
	return h;
}

/**
    @brief  Elimina uma operação da lista através do seu código
    @param  h      - Início da lista de operações
    @param  codigo - Código da operação a eliminar
    @return        - Lista de operações (início)
**/
Operacao* removerOperacao(Operacao* h, int codigo) {
	if (h == NULL) return NULL;							// Lista vazia

	if (h->codigo == codigo) {							// remove no inicio da lista
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}
	else {
		Operacao* aux = h;
		Operacao* auxAnt = aux;
		while (aux && aux->codigo != codigo) {	// Percorre a lista "à procura"
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {				// Quando encontrar, liberta.

			removerListaMaquinas(aux->listaMaquinas); 

			auxAnt->next = aux->next;
			free(aux);
		}
		return h;
	}
}

/**
    @brief  Verifica se a operação já existe na lista de operações. Compara o código das operações
    @param  h      - Início da lista de operações
    @param  codigo - Código da operação 
    @return       - True se a operação existir; False se não existe
**/
bool existeOperacao(Operacao* h, int codigo) {
	if (h == NULL) return false;
	Operacao* aux = h;
	while (aux != NULL) {
		if (aux->codigo == codigo) return true;
		aux = aux->next;
	}
	return false;
}

/**
    @brief  Verifica se a operação já existe na lista de operações. Compara o código das operações
    @param  h      - Início da lista de operações
    @param  codigo - Código da operação 
    @return        - Devolve NULL se não existir; Retorna um apontador para a operação se existir.
**/
Operacao* existeOperacaoPtr(Operacao* h, int codigo) {
	if (h == NULL) return NULL;
	Operacao* aux = h;
	while (aux != NULL) {
		if (aux->codigo == codigo) return aux;
		aux = aux->next;
	}
	return NULL;
}

/**
    @brief Mostra as maquinas que podem realizar cada operação
    @param h - Início da lista de operações
**/
void mostrarListaOperacaoeMaquinas(Operacao* h) {
	Operacao* aux = h;
	while (aux != NULL) {

		Maquina* auxMaq = aux->listaMaquinas;
		while (auxMaq != NULL)
		{
			printf("Operacao %d: maquina %s\n", aux->codigo, auxMaq->id);
			auxMaq = auxMaq->next;
		}
		aux = aux->next;

	}
}

#pragma endregion


#pragma region Maquina

/**
    @brief  Cria máquinas com a estrutura de Maquina
    @param  id    - Código identificador da máquina
    @param  tempo - Tempo que a máquina demora para realizar a operação
    @return       - Nova máquina
**/
Maquina* criarMaquina(char* id, int tempo) {
	Maquina* novaMaquina = (Maquina*)malloc(sizeof(Maquina));
	if (novaMaquina == NULL) return NULL;
	strcpy(novaMaquina->id, id);
	novaMaquina->tempo = tempo;
	novaMaquina->next = NULL;
	return novaMaquina;
}

/**
    @brief  Inserir máquinas numa lista de máquina
    @param  h    - Início da lista de máquinas
    @param  nova - Máquina a inserir
    @return      - Lista de máquinas
**/
Maquina* inserirMaquina(Maquina* h, Maquina* nova) {

	if (h == NULL) {					//se lista vazia, insere no inicio
		h = nova;
		return (h);
	}
	else
	{
		Maquina* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		if (aux != NULL)
		{
			aux->next = nova;
		}
	} return h;
}

/**
    @brief  Inserir máquinas na lista de operações. Procura o código da operação e insere a máquina.
    @param  h       - Início da lista de operações
    @param  codOper - Código da operação
    @param  m       - Máquina a inserir
    @return         - Lista de operações
**/
Operacao* inserirMaquinaOperacao(Operacao* h, int codOper, Maquina* maq) {

	if (h == NULL) return NULL;		// se lista vazia
	else
	{				//procura
		Operacao* aux = h;
		while (aux != NULL && aux->codigo != codOper) {
			aux = aux->next;
		}
		if (aux != NULL) {		//encontrou

			aux->listaMaquinas = inserirMaquina(aux->listaMaquinas, maq);
		}
	}
	return (h);
}

/**
    @brief  Remove lista de máquinas
    @param  h - Início da lista
    @return   - Lista de máquinas
**/
Maquina* removerListaMaquinas(Maquina* h) {
	Maquina* auxMaq;

	auxMaq = h;
	while (auxMaq != NULL) {
		h = auxMaq->next;
		free(auxMaq);
		auxMaq = h;
	}
	return h;
}

/**
    @brief  Verifica se uma máquina existe na lista de máquinas.
    @param  h          - Início da lista de máquinas
    @param  idMaquina  - ID da máquina 
    @return            - False se a máquina não existir; True se a máquina já existir
**/
bool existeMaquina(Maquina* h, int idMaquina) {
	if (h == NULL) return false;
	Maquina* auxMaq = h;
	while (auxMaq) {
		if (auxMaq->id == idMaquina) return true;
		auxMaq = auxMaq->next;
	}
	return false;
}
#pragma endregion


#pragma region Tempo

/**
    @brief Determinação do tempo mínimo necessário para completar o job
    @param h - Apontador para início da lista de operações
**/
void tempoMinimo(Operacao* h) {
	Operacao* auxOp = h;
	Maquina* auxMaq;
	int tempoMinimo;
	int resultado = 0;

	while (auxOp != NULL) { // Entra na lista de operações 

		auxMaq = auxOp->listaMaquinas;

		tempoMinimo = auxMaq->tempo;

		while (auxMaq != NULL) {
			if (auxMaq->tempo < tempoMinimo) {
				tempoMinimo = auxMaq->tempo;
			}
			
			auxMaq = auxMaq->next;
		}
		resultado += tempoMinimo;

		printf("Operacao %d - Tempo minimo: %d\n", auxOp->codigo, tempoMinimo);

		auxOp = auxOp->next;
	}
	printf("Total Minimo: %d\n", resultado);
}

/**
    @brief Determinação do tempo máximo necessário para completar o job
    @param h - Apontador para início da lista de operações
**/
void tempoMaximo(Operacao* h) {
	Operacao* auxOp = h;
	Maquina* auxMaq;
	int tempoMaximo = 0;
	int resultado = 0;

	while (auxOp != NULL) {
		tempoMaximo = 0;

		auxMaq = auxOp->listaMaquinas;

		while (auxMaq != NULL) {
			if (auxMaq->tempo > tempoMaximo) {
				tempoMaximo = auxMaq->tempo;
			}

			auxMaq = auxMaq->next;
		}

		resultado += tempoMaximo;
		printf("Operacao %d - Tempo maximo %d\n", auxOp->codigo, tempoMaximo);
		auxOp = auxOp->next;
	}
	printf("Total maximo: %d\n ", resultado);
}

/**
    @brief Determinação do tempo médio para completar o job
    @param h - Apontador para início da lista de operações
**/
void tempoMedio(Operacao* h) {
	Operacao* auxOp = h;
	Maquina* auxMaq;
	float soma = 0;
	int contadorMaq = 0;
	float resultado = 0;
	float resultadoMaq = 0;

	while (auxOp != NULL) {
		soma = 0;
		contadorMaq = 0;

		auxMaq = auxOp->listaMaquinas;

		while (auxMaq != NULL) {
			soma += auxMaq->tempo;
			contadorMaq++;
			auxMaq = auxMaq->next;
		}
		resultadoMaq = soma / contadorMaq;
		printf("Media da Operacao %d: %.2f \n", auxOp->codigo, resultadoMaq);

		resultado += resultadoMaq;
		auxOp = auxOp->next;
	}

	printf("Duracao media: %.2f\n", resultado);
}