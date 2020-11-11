#include <stdio.h>
#include <stdlib.h>

// Função que calcula e devolve os coeficientes do polinômio interpolador utilizando
// o método das diferenças divididas de Newton.
// x e y são vetores representandos as coordenadas dos pontos
// n é o número de pontos
// retornamos um vetor com n coeficientes na ordem a0, a1, a2 ... an
double *newton(double *x, double *y, int n) {
	double **m;
	double *coefs;

	// Vamos criar a matriz para fazer as computações
	m = malloc(sizeof(double *) * (n));                                  // allocando n linhas
	for (int i = 0; i < n; i++) m[i] = malloc(sizeof(double) * (n + 1)); // allocando n+1 colunas

	// Agora alocamos o vetor de coeficientes
	coefs = malloc(sizeof(double) * n);

	// Inicializando a matriz
	for (int i = 0; i < n; i++) {
		m[i][0] = x[i];
		m[i][1] = y[i];
	}

	// Computando a matriz
	for (int j = 2; j <= n; j++) {
		for (int i = j - 1; i < n; i++) {
			m[i][j] = (m[i][j - 1] - m[i - 1][j - 1]) / (m[i][0] - m[i - j + 1][0]);
		}
	}

	/* for (int i = 0; i < n; i++) { */
	/* for (int j = 0; j < n+1; j++) printf("%lf ", m[i][j]); */
	/* printf("\n"); */
	/* } */

	// Pegando os coeficientes na diagonal da matriz
	for (int j = 1; j <= n; j++) { coefs[j - 1] = m[j - 1][j]; }

	// Liberando a matriz de computações
	for (int i = 0; i < n; i++) free(m[i]);
	free(m);

	return coefs;
}

// Retorna o valor de f calculada no ponto x dados os coeficientes
// pré-calculados pelo método de Newton e os pontos de interpolação
double f(double x, double *x0, double *coefs, int n) {
	double fx;
	double prodx = 1;
	fx = coefs[0];

	for (int i = 1; i < n; i++) {
		prodx *= (x - x0[i - 1]);
		fx += coefs[i] * prodx;
	}
	return fx;
}

// Usa a regra do trapézio para integrar a função f no intervalo
// [a,b] utilizando n sub-intervalos.
double TrapezoidRule(int n, double a, double b, double *x0, double *coefs, int num_x) {
	double h = (b - a) / n;
	double TR = 0;

	TR += 0.5 * (f(a, x0, coefs, num_x) + f(b, x0, coefs, num_x));
	for (double i = a + h; i < b; i += h) {
		TR += f(i, x0, coefs, num_x);
	}
	TR *= h;

	return TR;
}

// Usa a regra de Simpson para integrar a função f no intervalo
// [a,b] utilizando n sub-intervalos.
double SimpsonRule(int n, double a, double b, double *x0, double *coefs, int num_x) {
	double h = (b - a) / n;
	double SR = 0;
  int j = 1;

	SR += (f(a, x0, coefs, num_x) + f(b, x0, coefs, num_x));
	for (double i = a + h; i < b; i += h, j++)
		SR += (j % 2 ? 4 : 2) * f(i, x0, coefs, num_x);
	SR *= (h / 3.0);

	return SR;
}

int main() {
	// Os vetores com os pontos dados no enunciado
	double x[] = { 0, 5, 10, 15, 20, 25, 30 };
	double y[] = { 0, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537 };
	int n = 7; // O número de pontos
	double *coefs = newton(x, y, n);

	/* for (int i = 0; i < n; i++) printf("coefs[%d] = %lf\n", i, coefs[i]); */

	/* for (double i = 0; i <= 30.001; i += 1) printf("p(%lf) = %lf\n", i, f(i, x, coefs, n)); */

	printf("Integral por trapézio: %lf\n", TrapezoidRule(100000, 0, 30, x, coefs, n));
	printf("Integral por Simpson: %lf\n", SimpsonRule(100000, 0, 30, x, coefs, n));

	free(coefs);
	return 0;
}
