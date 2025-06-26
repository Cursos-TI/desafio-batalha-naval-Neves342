#include <stdio.h>
#include <stdlib.h> // Para abs

#define TAM_TABULEIRO 10   // Tamanho do tabuleiro
#define TAM_NAVIO 3        // Tamanho dos navios
#define TAM_HAB 5          // Tamanho das matrizes de habilidade (5x5)

// Fun??o para verificar se uma posi??o est? ocupada
int ocupado(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    return tabuleiro[l][c] != 0;
}

// Fun??o para sobrepor matriz de habilidade no tabuleiro
void aplica_habilidade(int tab[TAM_TABULEIRO][TAM_TABULEIRO], int hab[TAM_HAB][TAM_HAB], int ol, int oc) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int l = ol + (i - centro);
                int c = oc + (j - centro);
                if (l >= 0 && l < TAM_TABULEIRO && c >= 0 && c < TAM_TABULEIRO) {
                    // S? marca como 5 se n?o for navio (3)
                    if (tab[l][c] != 3)
                        tab[l][c] = 5;
                }
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com ?gua (0)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // --- POSICIONAMENTO DOS NAVIOS ---
    // Coordenadas iniciais dos navios
    int l1 = 2, c1 = 1; // Horizontal
    int l2 = 5, c2 = 7; // Vertical
    int l3 = 0, c3 = 0; // Diagonal principal (?)
    int l4 = 0, c4 = 9; // Diagonal secund?ria (?)

    // Valida??o e posicionamento dos navios (igual ao n?vel aventureiro)
    // Horizontal
    if (c1 + TAM_NAVIO > TAM_TABULEIRO) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l1, c1 + i)) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l1][c1 + i] = 3;

    // Vertical
    if (l2 + TAM_NAVIO > TAM_TABULEIRO) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l2 + i, c2)) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l2 + i][c2] = 3;

    // Diagonal principal
    if (l3 + TAM_NAVIO > TAM_TABULEIRO || c3 + TAM_NAVIO > TAM_TABULEIRO) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l3 + i, c3 + i)) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l3 + i][c3 + i] = 3;

    // Diagonal secund?ria
    if (l4 + TAM_NAVIO > TAM_TABULEIRO || c4 - (TAM_NAVIO - 1) < 0) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l4 + i, c4 - i)) return 1;
    for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l4 + i][c4 - i] = 3;

    // --- MATRIZES DE HABILIDADE ---
    int cone[TAM_HAB][TAM_HAB] = {0};
    int cruz[TAM_HAB][TAM_HAB] = {0};
    int octaedro[TAM_HAB][TAM_HAB] = {0};

    // Preenche matriz cone (cone para baixo, centro no topo)
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i <= TAM_HAB/2 && j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                cone[i][j] = 1;
        }
    }

    // Preenche matriz cruz (linha e coluna central)
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                cruz[i][j] = 1;
        }
    }

    // Preenche matriz octaedro (losango)
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2)
                octaedro[i][j] = 1;
        }
    }

    // --- SOBREPOSI??O DAS HABILIDADES NO TABULEIRO ---
    // Pontos de origem das habilidades (centro das matrizes)
    int origem_cone_l = 4, origem_cone_c = 4;
    int origem_cruz_l = 7, origem_cruz_c = 2;
    int origem_octa_l = 7, origem_octa_c = 7;


    // Aplica as habilidades
    aplica_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);
    aplica_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);
    aplica_habilidade(tabuleiro, octaedro, origem_octa_l, origem_octa_c);

    // --- EXIBE O TABULEIRO FINAL ---
    printf("Tabuleiro de Batalha Naval com Habilidades Especiais:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ "); // ?gua
            else if (tabuleiro[i][j] == 3)
                printf("N "); // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* "); // ?rea de habilidade
            else
                printf("? "); // Caso inesperado
        }
        printf("\n");
    }

    // Aguarda o usu?rio pressionar ENTER antes de fechar
    printf("\nPressione ENTER para sair...");
    getchar();

    return 0;
}
