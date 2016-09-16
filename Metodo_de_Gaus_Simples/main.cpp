#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*------------------Description-------------------*/
/*                                                */
/*    Programmer: Carlos Eduardo Cuzik            */
/*    Institution: (BCC) UDESC-CCT                */
/*    GitHub: github.com/carloscuzik              */
/*    Functionality: Resolver problemas lineares  */
/*    Language: C/C++                             */
/*    Comments: Programa desenvolvido para a      */
/*    disciplina de Analize Numerica com o        */
/*    proposito de resolver problemas lineares.   */
/*    Compilation: g++ main.cpp -o exe && ./exe   */
/*                                                */
/*------------------------------------------------*/

/*------------Declaração das variaveis------------*/
int cont_linhas();
int cont_colunas();
double **Alocar_matriz_real(int n_linhas, int n_colunas);
double **Liberar_matriz_real(int n_linhas, int n_colunas, double **matriz);
double *Alocar_vetor_real(int n_espacos);
double *Liberar_vetor_real(int n_espacos, double *vetor);
void le_matriz(double **matriz_A,double *matriz_B);
void imprime_matriz(double **matriz_A,double *matriz_B, int linha,int coluna);
void metodo_da_eliminacao_de_gaus_simple(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas);
void imprime_resultado_final(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas);

int main(){
	int n_linhas = cont_linhas(); // pega o numero de linhas
	int n_colunas = cont_colunas(); // pega o numero de colunas
	double **matriz_A = Alocar_matriz_real(n_linhas,n_colunas-1); // cria a matriz_a 
	double *matriz_B = Alocar_vetor_real(n_linhas); // cria a matriz_b de resultados
	le_matriz(matriz_A,matriz_B); // le do arquivo de entrada para as matrizes no sistema
	imprime_matriz(matriz_A,matriz_B,n_linhas,n_colunas); // imprime a matriz sem alterações
	metodo_da_eliminacao_de_gaus_simple(matriz_A,matriz_B,n_linhas,n_colunas); // aplica eliminação de gaus nas matrizes
	imprime_resultado_final(matriz_A,matriz_B,n_linhas,n_colunas); // mostra a esultado de acordo com a formula
	return 0;
}

/*--------------Funções de contagem---------------*/
int cont_linhas(){
	FILE *in;
	in = fopen("entrada.txt","rt");
	char c;
	int count = 1;
	while((c = fgetc(in)) != EOF){
		if(c=='\n'){
			count++;
		}
	}
	return count;
}

int cont_colunas(){
	FILE *in;
	in = fopen("entrada.txt","rt");
	char c;
	int count = 1;
	while((c = fgetc(in)) != EOF){
		if(c==' '){
			count++;
		}
		if(c=='\n'){
			break;
		}
	}
	return count;
}


/*---------Alocando Dinamicamente Matrizes--------*/
double **Alocar_matriz_real(int n_linhas, int n_colunas){
	double **matriz;
	int i;
	if(n_linhas < 1 || n_colunas < 1){ // verifica se os parametros realmente formão uma matriz
		cout << ("Erro: Parametro invalido\n");
		return (NULL);
	}
	matriz = (double **) calloc (n_linhas, sizeof(double *)); // aloca o numero de linhas da matriz
	if(matriz == NULL) { // verifica se deu certo a alocão acima
		cout << ("Erro: Memoria Insuficiente\n");
		return (NULL);
	}
	for(i = 0;i < n_linhas;i++){
		matriz[i] = (double*) calloc(n_colunas, sizeof(double)); // vai alocando o numero de colunas de cada linha
		if (matriz[i] == NULL) { // verifica se ocorreu algum erro no processo acima
			cout << ("Erro: Memoria Insuficiente\n");
			return (NULL);
		}
	}
  return (matriz); // retorna a matriz alocada
}

double **Liberar_matriz_real(int n_linhas, int n_colunas, double **matriz){
	int i;
	if(matriz == NULL) return (NULL);
	if(n_linhas < 1 || n_colunas < 1){ // verifica se passo os parametros certos
		cout << ("Erro: Parametro invalido\n");
		return (matriz);
	}
	for(i=0; i<n_linhas; i++){
		free(matriz[i]); // libera as colunas de cada linha
	}
	free(matriz); // libera todas as linhas da matriz
	return (NULL); // retor vazio;
}

/*---------Alocando Dinamicamente Vetores---------*/
double *Alocar_vetor_real(int n_espacos){
	double *vetor;
	if(n_espacos < 1){
		printf("Erro: Parametro invalido\n");
		return (NULL);
	}
	vetor = (double *) calloc(n_espacos+1, sizeof(double)); // aloca o numero de linhsa
	if(vetor == NULL){ // verificase deu certo o processo acima
		printf("Erro: Memoria Insuficiente");
		return (NULL);
	}
	return (vetor); // retorna o vetor alocado
}

double *Liberar_vetor_real(int n_espacos, double *vetor){
	if(vetor == NULL){ // verifica se voce não passo um vetor vazio
		return (NULL);
	}
	if(n < 1){ // verifica se passo um numero de espaços possivel
		printf("Erro: Parametro invalido\n");
		return (NULL);
	}
	free(vetor); // libera os espaços do vetor
	return (NULL); // retor vazio;
}

/*----------Imprimindo a matriz na Tela-----------*/
void imprime_matriz(double **matriz_A,double *matriz_B, int linha,int coluna){
	int i,j;
	for(i=0;i<linha;i++){
		for(j=0;j<coluna-1;j++){
			if(matriz_A[i][j]>=0){
				cout << " ";
			}
			printf("%0.5lf ", matriz_A[i][j]); // imprime com 5 digitos depois da virgula
		}
		cout << "|";
		if(matriz_B[i]>=0){
			cout << " ";
		}
		printf("%0.5lf\n", matriz_B[i]); // imprime com 5 digitos depois da virgula
	}
	cout << endl;
}

/*---------------Laitura da matriz----------------*/
void le_matriz(double **matriz_A,double *matriz_B){
	FILE *in; // declara uma variavel do tipo arquivo
	in = fopen("entrada.txt","rt"); // passa o arquvo entrada.txt na forma de leitura(rt) para a variavel in
	int n_linhas = cont_linhas();
	int n_colunas = cont_colunas();
	int i,j;
	for(i=0;i<n_linhas;i++){
		for(j=0;j<n_colunas-1;j++){
			fscanf(in,"%lf",&matriz_A[i][j]); // le a matriz do arquivo e passa para a matriz_A
		}
		fscanf(in,"%lf",&matriz_B[i]); // le a matriz do arquivo e passa para a matriz_B que são os resultados
	}
}

/*-------------Metodo de Gaus na Matriz-----------*/
void metodo_da_eliminacao_de_gaus_simple(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas){
	int i,j,k;
	double m;
	for(i=0;i<n_linhas-1;i++){
		for(j=i+1;j<n_linhas;j++){
			m = -(matriz_A[j][i]/matriz_A[i][i]); // define o m para o calculo que zera abaixo da diagonal inferior
			matriz_A[j][i] = 0; // zera abaixo da diagonal inferior pois assim polpa a conta que vai dar zero mesmo
			for(k=i+1;k<n_colunas-1;k++){
				matriz_A[j][k] = m*matriz_A[i][k] + matriz_A[j][k]; // calcula o novo elemento da matriz e subistitui
			}
			matriz_B[j] = m*matriz_B[i] + matriz_B[j]; // calcula o novo resultado da linha e substitui
		}
		cout << "--->>Passo " << i+1 << ":" << endl;
		imprime_matriz(matriz_A,matriz_B,n_linhas,n_colunas);
	}
}

/*-------------Imprimindo o Resultado-------------*/
void imprime_resultado_final(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas){
	int i,j;
	double resultado[n_colunas-1];
	double parser;
	for(i=n_colunas-2;i>=0;i--){
		resultado[i] = 1.0/matriz_A[i][i]; // começo da formula é o inverso do Aii
		parser = matriz_B[i]; // o resultado parcial é calculado primeiro com o resultado da linha
		for(j=i+1;j<n_colunas-1;j++){
			parser -= matriz_A[i][j]*resultado[j]; // e a cada vez que passa pelo loop for multplica os elementos da linha pelos seus resultados que ja possui
		}
		resultado[i] *= parser; // por ultimo multiplica o resultado parcial com o que inverso de Aii
	}
	//Apenas para mostrar na tela de forma bonita:
	for(i=0;i<n_colunas-1;i++){
		cout << "x" << i+1 << ": ";
		if(resultado[i] >= 0){
			cout << " ";
		}
		cout << resultado[i] << endl;
	}
}