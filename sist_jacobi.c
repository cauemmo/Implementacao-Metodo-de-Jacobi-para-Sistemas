#include <stdio.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 10 // Tamanho máximo permitido para o sistema linear

void gaussJacobi(double A[MAX_SIZE][MAX_SIZE], double b[MAX_SIZE], double x[MAX_SIZE], int size, double tolerance, int maxIterations) {
    double xNew[MAX_SIZE];
    int i, j, k;
    double error, sum;

    for (k = 0; k < maxIterations; k++) {
        error = 0.0;

        // Calcula os novos valores para x
        for (i = 0; i < size; i++) {
            sum = 0.0;
            for (j = 0; j < size; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            xNew[i] = (b[i] - sum) / A[i][i];

            // Calcula o erro atual
            if (fabs(xNew[i] - x[i]) > error) {
                error = fabs(xNew[i] - x[i]);
            }
        }

        // Atualiza x
        for (i = 0; i < size; i++) {
            x[i] = xNew[i];
        }

        // Imprime o progresso da iteração
        printf("Iteração %d: ", k + 1);
        for (i = 0; i < size; i++) {
            printf("x[%d] = %.7f ", i, x[i]);
        }
        printf("\n");

        // Verifica a convergência
        if (error < tolerance) {
            printf("Convergência alcançada após %d iterações.\n", k + 1);
            return;
        }
    }

    printf("Número máximo de iterações atingido.\n");
}

int main() {
    int size;
    float tempo;
    time_t t_ini, t_fim;
    
    t_ini = time(NULL);

    printf("Digite o tamanho do sistema linear (até %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size <= 0 || size > MAX_SIZE) {
        printf("Tamanho inválido para o sistema linear.\n");
        return 0;
    }

    double A[MAX_SIZE][MAX_SIZE];
    double b[MAX_SIZE];
    double x[MAX_SIZE] = {0}; // Chute inicial

    printf("Digite os elementos da matriz A:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Digite a Solução inicial:\n");
    for (int i = 0; i < size; i++) {
        printf("b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    double tolerance;
    int maxIterations;

    printf("Digite a precisao: ");
    scanf("%lf", &tolerance);

    printf("Digite o número máximo de iterações: ");
    scanf("%d", &maxIterations);

    gaussJacobi(A, b, x, size, tolerance, maxIterations);

    // Imprime a solução
    printf("Solução:\n");
    for (int i = 0; i < size; i++) {
        printf("x[%d] = %.7f\n", i, x[i]);
    }
    t_fim = time(NULL);
    tempo =  difftime(t_fim, t_ini);
    printf("Tempo: %.1f\n",tempo);
return 0;
}