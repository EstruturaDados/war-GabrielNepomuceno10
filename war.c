#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================================
// 🔧 Constantes e Tipos
// ==========================================

#define QTD_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[30];
    int numTropas;
} Territorio;

typedef struct {
    int tipo; // 1 = destruir exército verde, 2 = conquistar 3 territórios
    int territoriosConquistados;
    int venceu;
} Missao;

// ==========================================
// 🧱 Funções auxiliares
// ==========================================

// Inicializa o gerador de números aleatórios
void inicializarAleatorio() {
    srand(time(NULL));
}

// Inicializa territórios automaticamente
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numTropas = (rand() % 5) + 2; // entre 2 e 6
    }
}

// Exibe o mapa atual
void exibirMapa(const Territorio *territorios) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("%d) %-10s | Cor: %-10s | Tropas: %d\n",
               i + 1, territorios[i].nome, territorios[i].corExercito, territorios[i].numTropas);
    }
    printf("----------------------------\n");
}

// Cria uma missão aleatória
void gerarMissao(Missao *missao) {
    missao->tipo = (rand() % 2) + 1; // 1 ou 2
    missao->territoriosConquistados = 0;
    missao->venceu = 0;

    printf("\n=== Missão Recebida ===\n");
    if (missao->tipo == 1)
        printf("🎯 Destruir o exército Verde!\n");
    else
        printf("🎯 Conquistar 3 territórios!\n");
    printf("----------------------------\n");
}

// Exibe o status da missão
void verificarMissao(const Missao *missao) {
    printf("\n=== Verificação da Missão ===\n");
    if (missao->venceu)
        printf("🏆 Missão concluída! Você venceu o jogo!\n");
    else if (missao->tipo == 1)
        printf("Missão: Destruir o exército Verde ainda está em andamento.\n");
    else
        printf("Missão: Conquistar 3 territórios (%d/3).\n", missao->territoriosConquistados);
    printf("----------------------------\n");
}

// Simula o ataque entre dois territórios
void simularAtaque(Territorio *territorios, Missao *missao, int atacante, int defensor) {
    if (atacante == defensor) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (territorios[atacante].numTropas <= 1) {
        printf("⚠️ %s não tem tropas suficientes para atacar!\n", territorios[atacante].nome);
        return;
    }

    printf("\n⚔️ Batalha: %s (Atacante) vs %s (Defensor)\n",
           territorios[atacante].nome, territorios[defensor].nome);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("🎲 Dado do atacante: %d | 🛡️ Dado do defensor: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        territorios[defensor].numTropas--;

        printf("🔥 O atacante venceu a rodada!\n");

        if (territorios[defensor].numTropas <= 0) {
            printf("🏳️ O território %s foi conquistado!\n", territorios[defensor].nome);
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = 1;
            territorios[atacante].numTropas--;

            // Atualiza missão
            if (missao->tipo == 2)
                missao->territoriosConquistados++;

            // Verifica se destruiu o exército verde
            if (missao->tipo == 1) {
                int existeVerde = 0;
                for (int i = 0; i < QTD_TERRITORIOS; i++) {
                    if (strcmp(territorios[i].corExercito, "Verde") == 0)
                        existeVerde = 1;
                }
                if (!existeVerde)
                    missao->venceu = 1;
            }

            // Verifica se completou conquista de 3 territórios
            if (missao->tipo == 2 && missao->territoriosConquistados >= 3)
                missao->venceu = 1;
        }
    } else {
        printf("🛡️ O defensor resistiu!\n");
        territorios[atacante].numTropas--;
    }

    exibirMapa(territorios);
}

// ==========================================
// 🕹️ Função principal (menu interativo)
// ==========================================

int main() {
    inicializarAleatorio();

    Territorio *territorios = calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    Missao missao;
    inicializarTerritorios(territorios);
    gerarMissao(&missao);

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1: {
                int at, def;
                exibirMapa(territorios);
                printf("Escolha o atacante (1-%d): ", QTD_TERRITORIOS);
                scanf("%d", &at);
                printf("Escolha o defensor (1-%d): ", QTD_TERRITORIOS);
                scanf("%d", &def);
                getchar();

                simularAtaque(territorios, &missao, at - 1, def - 1);

                if (missao.venceu) {
                    printf("\n🏆 Parabéns! Você completou sua missão!\n");
                    opcao = 0; // encerra o jogo
                }
                break;
            }
            case 2:
                verificarMissao(&missao);
                break;
            case 0:
                printf("👋 Encerrando o jogo...\n");
                break;
            default:
                printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);

    free(territorios);
    return 0;
}
