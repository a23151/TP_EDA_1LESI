#include "dadosFuncoes.h"
#include "dadosEscalonamento.h"

#pragma warning( disable : 4996 )

int main() {
	Planeamento plano[9][T];

	Celula auxiliar[T];

	Job* root = iniciarArvore();

	root=lerFicheiroTexto();
	//mostrarArvore(root);


	iniciarArrayAuxiliar(auxiliar);

	iniciaPlano(plano);

	preencherArrayArvore(root, auxiliar);

	ocupaPlano(plano, auxiliar);
	
	exportarPlanoCsv(plano);


	//root= removerJob(root, 2);

	
//	guardarArvoreFicheiro(root, "teste.bin");

	/*Celula aux;
	aux.codigoJob = 1;
	aux.codigoOper = 2;
	strcpy(aux.idMaq, "M2");
	aux.tempo = 2;
	int a;
	a = devolvemaquina(&aux);*/
}
