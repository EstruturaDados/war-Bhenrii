#include <stdio.h>

#define MAX_NOME 100
#define QTD_TERRITORIOS 5

struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_NOME];
    int numero;
};

int main() {
    struct Territorio territorio[QTD_TERRITORIOS];
    int totaltropa = 0;

    while (totaltropa < QTD_TERRITORIOS) {
        printf("==========================================================\n");
        printf(" VAMOS CADASTRAR OS TERRITORIOS INICIAIS DO NOSSO MUNDO\n");
        printf(" --- CADASTRANDO TERRITORIO %d ---\n", totaltropa + 1);

        printf("    NOME DO TERRITORIO: ");
        fgets(territorio[totaltropa].nome, MAX_NOME, stdin);

        printf("    COR DO EXERCITO: ");
        fgets(territorio[totaltropa].cor, MAX_NOME, stdin);

        printf("    NÚMERO DE TROPAS: ");
        scanf("%d", &territorio[totaltropa].numero);
        getchar(); // limpa o \n deixado pelo scanf

        totaltropa++;
    }

    printf("\nCadastro inicial concluído com sucesso!\n\n");
    printf("==============================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL  \n");
    printf("==============================================\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf(" - Nome: %s", territorio[i].nome);
        printf(" - Dominado por: %s", territorio[i].cor);
        printf(" - Tropas: %d\n", territorio[i].numero);
        printf("----------------------------------------------\n");
    }

    return 0;
}
