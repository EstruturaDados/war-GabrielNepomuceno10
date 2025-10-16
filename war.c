#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *territorios, int qtd) {
    printf("=== Cadastro de Territórios ===\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // limpar o '\n' deixado pelo scanf

        printf("\n");
    }
}

// Função para exibir o estado atual do mapa
void exibirMapa(Territorio *territorios, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("----------------------------\n");
    }
}

// Função para simular um ataque entre dois territórios
void simularAtaque(Territorio *territorios, int atacante, int defensor) {
    if (atacante == defensor) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (territorios[atacante].numTropas <= 1) {
        printf("⚠️ O território %s não tem tropas suficientes para atacar!\n",
               territorios[atacante].nome);
        return;
    }

    printf("\n⚔️ Batalha entre %s (Atacante) e %s (Defensor)\n",
           territorios[atacante].nome, territorios[defensor].nome);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("🎲 Dado do atacante: %d\n", dadoAtacante);
    printf("🛡️ Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        territorios[defensor].numTropas--;

        printf("🔥 O atacante venceu a rodada!\n");

        if (territorios[defensor].numTropas <= 0) {
            printf("🏳️ O território %s foi conquistado!\n", territorios[defensor].nome);

            // Transferência de controle (opcional)
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = 1; // atacante move uma tropa
            territorios[atacante].numTropas--;
        }
    } else {
        printf("🛡️ O defensor resistiu ao ataque!\n");
        territorios[atacante].numTropas--;
    }

    printf("\n--- Resultado Após a Batalha ---\n");
    printf("%s → Tropas: %d\n", territorios[atacante].nome, territorios[atacante].numTropas);
    printf("%s → Tropas: %d\n", territorios[defensor].nome, territorios[defensor].numTropas);
    printf("----------------------------\n");
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(territorios, QTD_TERRITORIOS);
    exibirMapa(territorios, QTD_TERRITORIOS);

    int atacante, defensor;
    char opcao;

    // Laço interativo de ataques
    do {
        printf("\n=== Fase de Ataque ===\n");
        printf("Escolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &atacante);
        printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &defensor);
        getchar(); // limpar buffer

        simularAtaque(territorios, atacante - 1, defensor - 1);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);
        getchar();

        exibirMapa(territorios, QTD_TERRITORIOS);

    } while (opcao == 's' || opcao == 'S');

    free(territorios); // libera memória alocada
    printf("\n🗺️ Fim da simulação!\n");

    return 0;
}
