#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

int main() {
    Territorio territorios[QTD_TERRITORIOS];

    printf("=== Cadastro de Territórios ===\n\n");

    // Leitura dos dados dos 5 territórios
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // limpa o '\n' do buffer antes do próximo fgets

        printf("\n");
    }

    // Exibição dos dados
    printf("\n=== Estado Atual do Mapa ===\n\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("----------------------------\n");
    }

    return 0;
}
