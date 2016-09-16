#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int cont_linhas();
int cont_colunas();
double **Alocar_matriz_real(int m, int n);
double **Liberar_matriz_real(int m, int n, double **v);
double *Alocar_vetor_real(int n);
double *Liberar_vetor_real(int n, double *v);
void le_matriz(double **matriz_A,double *matriz_B);
void imprime_matriz(double **matriz_A,double *matriz_B, int linha,int coluna);
void metodo_da_eliminacao_de_gaus_simple(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas);
void imprime_resultado_final(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas);

int main(){
	int n_linhas = cont_linhas();
	int n_colunas = cont_colunas();
	cout << "matriz: " << n_linhas << " x " << n_colunas-1 << endl;
	double **matriz_A = Alocar_matriz_real(n_linhas,n_colunas-1);
	double *matriz_B = Alocar_vetor_real(n_linhas);
	le_matriz(matriz_A,matriz_B);
	imprime_matriz(matriz_A,matriz_B,n_linhas,n_colunas);
	metodo_da_eliminacao_de_gaus_simple(matriz_A,matriz_B,n_linhas,n_colunas);
	imprime_resultado_final(matriz_A,matriz_B,n_linhas,n_colunas);
	return 0;
}

/************Funções de Contagem**************/

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

/**************Alocando Matrizes***************/

double **Alocar_matriz_real(int m, int n){
	double **v;
	int i;
	if(m < 1 || n < 1){
		cout << ("Erro: Parametro invalido\n");
		return (NULL);
	}
	v = (double **) calloc (m, sizeof(double *));
	if(v == NULL) {
		cout << ("Erro: Memoria Insuficiente\n");
		return (NULL);
	}
	for(i = 0;i < m;i++){
		v[i] = (double*) calloc(n, sizeof(double));
		if (v[i] == NULL) {
			cout << ("Erro: Memoria Insuficiente\n");
			return (NULL);
		}
	}
  return (v);
}

double **Liberar_matriz_real(int m, int n, double **v){
	int i;
	if(v == NULL) return (NULL);
	if(m < 1 || n < 1){
		cout << ("Erro: Parametro invalido\n");
		return (v);
	}
	for(i=0; i<m; i++){
		free(v[i]);
	}
	free(v);
	return (NULL);
}

/**************Alocando Vetores***************/

double *Alocar_vetor_real(int n){
	double *v;
	if(n < 1){
		printf("Erro: Parametro invalido\n");
		return (NULL);
	}
	v = (double *) calloc(n+1, sizeof(double));
	if(v == NULL){
		printf("Erro: Memoria Insuficiente");
		return (NULL);
	}
	return (v);
}

double *Liberar_vetor_real(int n, double *v){
	if(v == NULL){
		return (NULL);
	}
	if(n < 1){
		printf("Erro: Parametro invalido\n");
		return (NULL);
	}
	free(v);
	return (NULL);
}
/************Mostra Matriz***************/
void imprime_matriz(double **matriz_A,double *matriz_B, int linha,int coluna){
	int i,j;
	for(i=0;i<linha;i++){
		for(j=0;j<coluna-1;j++){
			//cout << matriz_A[i][j] << " ";
			if(matriz_A[i][j]>=0){
				cout << " ";
			}
			printf("%5.5lf ", matriz_A[i][j]);
		}
		cout << "|";
		if(matriz_B[i]>=0){
			cout << " ";
		}
		printf("%5.5lf\n", matriz_B[i]);
	}
	cout << endl;
}

/************Leitura da Matriz**************/

void le_matriz(double **matriz_A,double *matriz_B){
	FILE *in;
	in = fopen("entrada.txt","rt");
	int n_linhas = cont_linhas();
	int n_colunas = cont_colunas();
	int i,j;
	for(i=0;i<n_linhas;i++){
		for(j=0;j<n_colunas-1;j++){
			fscanf(in,"%lf",&matriz_A[i][j]);
		}
		fscanf(in,"%lf",&matriz_B[i]);
	}
}

/************Metodo de gaus da matriz**************/

void metodo_da_eliminacao_de_gaus_simple(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas){
	int i,j,k;
	double m, aux;
	for(i=0;i<n_linhas-1;i++){
		for(j=i+1;j<n_linhas;j++){
			m = -(matriz_A[j][i]/matriz_A[i][i]);
			matriz_A[j][i] = 0;
			for(k=i+1;k<n_colunas-1;k++){
				matriz_A[j][k] = m*matriz_A[i][k] + matriz_A[j][k];
			}
			matriz_B[j] = m*matriz_B[i] + matriz_B[j];
		}
		cout << "--->>Passo " << i+1 << ":" << endl;
		imprime_matriz(matriz_A,matriz_B,n_linhas,n_colunas);
	}
}

/*******Imprime o Resultado Final**********/

void imprime_resultado_final(double **matriz_A,double *matriz_B, int n_linhas,int n_colunas){
	int i,j;
	double resultado[n_colunas-1];
	double parser;
	for(i=n_colunas-2;i>=0;i--){
		resultado[i] = 1.0/matriz_A[i][i];
		parser = matriz_B[i];
		for(j=i+1;j<n_colunas-1;j++){
			parser -= matriz_A[i][j]*resultado[j];
		}
		resultado[i] *= parser; 
	}

	for(i=0;i<n_colunas-1;i++){
		cout << "x" << i+1 << ": ";
		if(resultado[i] >= 0){
			cout << " ";
		}
		cout << resultado[i] << endl;
	}
}