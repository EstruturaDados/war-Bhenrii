#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 100
#define QTD_TERRITORIOS 5
#define QTD_MISSOES 5

struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_NOME];
    int numero; // número de tropas
};

// ---------- FUNÇÕES DO JOGO ----------

// Mostra o estado atual do mapa
void mostrarMapa(struct Territorio territorio[], int total) {
    printf("\n================ MAPA ATUAL ================\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %-15s | Exército: %-10s | Tropas: %d\n",
               i + 1, territorio[i].nome, territorio[i].cor, territorio[i].numero);
    }
    printf("============================================\n");
}

// Realiza o ataque entre dois territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("%s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("ATAQUE (%s): %d | DEFESA (%s): %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITÓRIA DO ATACANTE! O defensor perdeu 1 tropa.\n");
        defensor->numero -= 1;
        if (defensor->numero <= 0) {
            printf("O território %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->numero = 1;
        }
    } else {
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->numero -= 1;
        if (atacante->numero <= 0) {
            atacante->numero = 0;
            printf("%s ficou sem tropas!\n", atacante->nome);
        }
    }

    printf("\nPRESSIONE ENTER PARA CONTINUAR...");
    getchar();
    getchar();
}

// Sorteia uma missão para o jogador
void atribuirMissao(char **missao, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *missao = (char *)malloc(strlen(missoes[indice]) + 1);
    strcpy(*missao, missoes[indice]);
}

// Exibe a missão atual do jogador
void exibirMissao(char *cor, char *missao) {
    printf("\n-- SUA MISSÃO, EXÉRCITO %s --\n", cor);
    printf("%s\n", missao);
}

// Verifica se a missão foi cumprida (lógica básica)
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho, char *corJogador) {
    // Exemplo: “Conquistar 3 territórios”
    if (strstr(missao, "Conquistar") != NULL) {
        int conquistas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistas++;
        }
        if (conquistas >= 3)
            return 1; // missão cumprida
    }

    // Exemplo: “Eliminar todas as tropas vermelhas”
    if (strstr(missao, "vermelho") != NULL) {
        int existeVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].numero > 0)
                existeVermelho = 1;
        }
        if (!existeVermelho)
            return 1; // missão cumprida
    }

    return 0; // ainda não
}

// Libera memória alocada
void liberarMemoria(char *missao) {
    free(missao);
}

// ---------- FUNÇÃO PRINCIPAL ----------
int main() {
    srand(time(NULL));

    struct Territorio territorio[QTD_TERRITORIOS];
    int totaltropa = 0;

    char *missoes[QTD_MISSOES] = {
        "Conquistar 3 territórios.",
        "Eliminar todas as tropas vermelhas.",
        "Dominar 2 territórios seguidos.",
        "Manter todos os seus territórios com mais de 3 tropas.",
        "Conquistar todos os territórios verdes."
    };

    char *missaoJogador = NULL;

    // Cadastro inicial dos territórios
    while (totaltropa < QTD_TERRITORIOS) {
        printf("\n--- CADASTRANDO TERRITÓRIO %d ---\n", totaltropa + 1);

        printf("Nome do território: ");
        fgets(territorio[totaltropa].nome, MAX_NOME, stdin);
        territorio[totaltropa].nome[strcspn(territorio[totaltropa].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(territorio[totaltropa].cor, MAX_NOME, stdin);
        territorio[totaltropa].cor[strcspn(territorio[totaltropa].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &territorio[totaltropa].numero);
        getchar(); // limpa buffer

        totaltropa++;
    }

    printf("\nCadastro inicial concluído!\n");

    // Sorteia missão para o primeiro jogador (exemplo)
    atribuirMissao(&missaoJogador, missoes, QTD_MISSOES);
    printf("\nMissão sorteada para o exército %s:\n", territorio[0].cor);
    printf("%s\n", missaoJogador);

    int opcao, atacante, defensor;
    while (1) {
        mostrarMapa(territorio, QTD_TERRITORIOS);

        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1. ATACAR\n");
        printf("2. VERIFICAR MISSÃO\n");
        printf("0. SAIR\n");
        printf("Escolha sua ação: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("\nEncerrando o jogo...\n");
            break;
        }

        if (opcao == 2) {
            if (verificarMissao(missaoJogador, territorio, QTD_TERRITORIOS, territorio[0].cor)) {
                printf("\nParabéns! Você concluiu sua missão e venceu o jogo!\n");
                break;
            } else {
                printf("\nMissão ainda não foi concluída.\n");
            }
        }

        if (opcao == 1) {
            printf("\nEscolha o território atacante (1 a 5): ");
            scanf("%d", &atacante);
            printf("Escolha o território defensor (1 a 5): ");
            scanf("%d", &defensor);

            if (atacante == defensor) {
                printf("Não é possível atacar o próprio território!\n");
                continue;
            }

            atacar(&territorio[atacante - 1], &territorio[defensor - 1]);

            // Game Over se o exército do jogador ficar sem tropas
            int totalTropas = 0;
            for (int i = 0; i < QTD_TERRITORIOS; i++) {
                if (strcmp(territorio[i].cor, territorio[0].cor) == 0)
                    totalTropas += territorio[i].numero;
            }

            if (totalTropas <= 0) {
                printf("\nGAME OVER! Seu exército foi derrotado.\n");
                break;
            }

            if (verificarMissao(missaoJogador, territorio, QTD_TERRITORIOS, territorio[0].cor)) {
                printf("\nPARABÉNS! Você concluiu sua missão e venceu o jogo!\n");
                break;
            }
        }
    }

    liberarMemoria(missaoJogador);
    printf("\nJogo finalizado.\n");
    return 0;
}
