#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double montecarlo(int n, double (*f)(double *), double **limits, int m) {
	double media = 0;
	double mc = 1;
	double *X; // A variável X de m dimensões

	X = malloc(sizeof(double) * m);

	double aux;

	// Calculando a média:
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			// Calculando cada coordenada de X randomicamente
			X[j] = (limits[j][1] - limits[j][0]) * ((double)rand() / RAND_MAX) + limits[j][0];
			/* printf("X[%d] = %lf\n", j, X[j]); */
		}
		aux = f(X);
		/* printf("f(X) = %.16lf\n", aux); */

		// Avaliamos a função nesse ponto aleatório e somamos à média
		media += f(X);
	}

	// Ao final, dividimos por n para obter a média
	media /= n;

	// Agora precisamos multiplicar pelo volume da superfície:
	// O volume é a integral múltipla da função identidade 1 em cada um dos eixos coordenados
	// Ou seja, basta fazer a multiplicação dos limites e isso nos dá o volume
	for (int j = 0; j < m; j++) mc *= (limits[j][1] - limits[j][0]);

	/* printf("mc = %lf\n", mc); */
	/* printf("media = %lf\n", media); */

	mc *= media; // E ao final multiplicamos pela média para ter a integral aproximada

	free(X);
	return mc;
}

double f1(double *x) { return sin(x[0]); }

void questao1() {
	double **limits; // Os limites em cada eixo coordenado
	double m = 1;    // O número de dimensões

	// Alocando a matriz dos limites
	limits = malloc(sizeof(double *) * m);
	for (int i = 0; i < m; i++) limits[i] = malloc(sizeof(double) * 2);

	// Definindo os limites
	limits[0][0] = 0;
	limits[0][1] = 1;

	printf("Integral de sin(x) de 0 a 1 = %lf\n", montecarlo(100000000, &f1, limits, m));

	// Liberando a matriz dos limites
	for (int i = 0; i < m; i++) free(limits[i]);
	free(limits);
}

double f2(double *x) { return x[0] * x[0] * x[0]; }

void questao2() {
	double **limits; // Os limites em cada eixo coordenado
	double m = 1;    // O número de dimensões

	// Alocando a matriz dos limites
	limits = malloc(sizeof(double *) * m);
	for (int i = 0; i < m; i++) limits[i] = malloc(sizeof(double) * 2);

	// Definindo os limites
	limits[0][0] = 3;
	limits[0][1] = 7;

	printf("Integral de x^3 de 3 a 7 = %lf\n", montecarlo(100000000, &f2, limits, m));

	// Liberando a matriz dos limites
	for (int i = 0; i < m; i++) free(limits[i]);
	free(limits);
}

double f3(double *x) { return pow(exp(1), -x[0]); }

void questao3() {
	double **limits; // Os limites em cada eixo coordenado
	double m = 1;    // O número de dimensões

	// Alocando a matriz dos limites
	limits = malloc(sizeof(double *) * m);
	for (int i = 0; i < m; i++) limits[i] = malloc(sizeof(double) * 2);

	// Definindo os limites
	limits[0][0] = 0;
	limits[0][1] = 10;

	printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));

	// Liberando a matriz dos limites
	for (int i = 0; i < m; i++) free(limits[i]);
	free(limits);
}

double f4(double *x) { return (x[0] * x[0] + x[1] * x[1] <= 1.0 ? 1 : 0); }

void questao4() {
	double **limits; // Os limites em cada eixo coordenado
	double m = 2;    // O número de dimensões

	// Alocando a matriz dos limites
	limits = malloc(sizeof(double *) * m);
	for (int i = 0; i < m; i++) limits[i] = malloc(sizeof(double) * 2);

	// Definindo os limites
	limits[0][0] = 0;
	limits[0][1] = 1;
	limits[1][0] = 0;
	limits[1][1] = 1;

	printf("pi = %lf\n", 4 * montecarlo(100000000, &f4, limits, m));

	// Liberando a matriz dos limites
	for (int i = 0; i < m; i++) free(limits[i]);
	free(limits);
}

void questao3testes() {
	double **limits; // Os limites em cada eixo coordenado
	double m = 1;    // O número de dimensões

	// Alocando a matriz dos limites
	limits = malloc(sizeof(double *) * m);
	for (int i = 0; i < m; i++) limits[i] = malloc(sizeof(double) * 2);

	// Definindo os limites
	limits[0][0] = 0;
	limits[0][1] = 1;

	printf("Testando para inf = 1:\n");
	for (int i = 0; i < 5; i++)
		printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));
  printf("\n");

	limits[0][1] = 10;
	printf("Testando para inf = 10:\n");
	for (int i = 0; i < 5; i++)
		printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));
  printf("\n");

	limits[0][1] = 100;
	printf("Testando para inf = 100:\n");
	for (int i = 0; i < 5; i++)
		printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));
  printf("\n");

	limits[0][1] = 1000;
	printf("Testando para inf = 1000:\n");
	for (int i = 0; i < 5; i++)
		printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));
  printf("\n");

	limits[0][1] = 100000;
	printf("Testando para inf = 100000:\n");
	for (int i = 0; i < 5; i++)
		printf("Integral de e^(-x) de 0 a infinito = %lf\n", montecarlo(100000000, &f3, limits, m));
  printf("\n");

	// Liberando a matriz dos limites
	for (int i = 0; i < m; i++) free(limits[i]);
	free(limits);
}

int main() {
	srand(time(0)); // Iniciando o gerador de números aleatórios

  questao1();
  questao2();
  questao3();
  questao4();
  /* questao3testes(); */

	return 0;
}
