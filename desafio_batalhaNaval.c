#include <stdio.h>
#include <stdlib.h> // Necessario para usar abs(), dando erros
// Aluna: Yasmin Neves
// Bem vinda(o) ao Desafio da Batalha Naval
// Testando novos aprendizados e organizando o codigo

#define TAM_TABULEIRO 10   // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3        // Tamanho dos navios (3 casas)
#define TAM_HAB 5          // Tamanho das matrizes de habilidade (5x5)

// Funcao para verificar se uma posicao do tabuleiro ja esta ocupada por um navio ou habilidade
int ocupado(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    return tabuleiro[l][c] != 0;
}

// Funcao para aplicar uma matriz de habilidade no tabuleiro
// Marca as posicoes afetadas pela habilidade com o valor 5, desde que nao haja navio (3)
void aplica_habilidade(int tab[TAM_TABULEIRO][TAM_TABULEIRO], int hab[TAM_HAB][TAM_HAB], int ol, int oc) {
    int centro = TAM_HAB / 2; // Calcula o centro da matriz de habilidade
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) { // Se a posicao faz parte da area de efeito
                int l = ol + (i - centro); // Calcula a linha correspondente no tabuleiro
                int c = oc + (j - centro); // Calcula a coluna correspondente no tabuleiro
                // Verifica se esta dentro dos limites do tabuleiro
                if (l >= 0 && l < TAM_TABULEIRO && c >= 0 && c < TAM_TABULEIRO) {
                    // Marca como 5 apenas se nao houver navio (3)
                    if (tab[l][c] != 3)
                        tab[l][c] = 5;
                }
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com agua (0 em todas as posicoes)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};
    int i, j;

    // --- POSICIONAMENTO DOS NAVIOS ---
    // Coordenadas iniciais dos navios
    int l1 = 2, c1 = 1; // Navio horizontal (linha 2, coluna 1)
    int l2 = 5, c2 = 7; // Navio vertical (linha 5, coluna 7)
    int l3 = 0, c3 = 0; // Navio diagonal principal (linha 0, coluna 0)
    int l4 = 0, c4 = 9; // Navio diagonal secundaria (linha 0, coluna 9)

    // Validacao e posicionamento dos navios
    // Navio horizontal
    if (c1 + TAM_NAVIO > TAM_TABULEIRO) return 1; // Verifica se cabe no tabuleiro
    for (i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l1, c1 + i)) return 1; // Verifica sobreposicao
    for (i = 0; i < TAM_NAVIO; i++) tabuleiro[l1][c1 + i] = 3; // Posiciona navio

    // Navio vertical
    if (l2 + TAM_NAVIO > TAM_TABULEIRO) return 1; // Verifica se cabe no tabuleiro
    for (i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l2 + i, c2)) return 1; // Verifica sobreposicao
    for (i = 0; i < TAM_NAVIO; i++) tabuleiro[l2 + i][c2] = 3; // Posiciona navio

    // Navio diagonal principal (de cima para baixo, esquerda para direita)
    if (l3 + TAM_NAVIO > TAM_TABULEIRO || c3 + TAM_NAVIO > TAM_TABULEIRO) return 1; // Limites
    for (i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l3 + i, c3 + i)) return 1; // Sobreposicao
    for (i = 0; i < TAM_NAVIO; i++) tabuleiro[l3 + i][c3 + i] = 3; // Posiciona navio

    // Navio diagonal secundaria (de cima para baixo, direita para esquerda)
    if (l4 + TAM_NAVIO > TAM_TABULEIRO || c4 - (TAM_NAVIO - 1) < 0) return 1; // Limites
    for (i = 0; i < TAM_NAVIO; i++) if (ocupado(tabuleiro, l4 + i, c4 - i)) return 1; // Sobreposicao
    for (i = 0; i < TAM_NAVIO; i++) tabuleiro[l4 + i][c4 - i] = 3; // Posiciona navio

    // --- MATRIZES DE HABILIDADE ---
    // Cada matriz representa a area de efeito de uma habilidade especial
    int cone[TAM_HAB][TAM_HAB] = {0};      // Cone para baixo
    int cruz[TAM_HAB][TAM_HAB] = {0};      // Cruz centralizada
    int octaedro[TAM_HAB][TAM_HAB] = {0};  // Octaedro (losango)

    // Preenche matriz cone (cone para baixo, centro no topo)
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // Marca 1 nas posicoes que formam o cone
            if (i <= TAM_HAB/2 && j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                cone[i][j] = 1;
        }
    }

    // Preenche matriz cruz (linha e coluna central)
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // Marca 1 na linha e coluna central
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                cruz[i][j] = 1;
        }
    }

    // Preenche matriz octaedro (losango)
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // Marca 1 nas posicoes que formam o losango
            if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2)
                octaedro[i][j] = 1;
        }
    }

    // --- SOBREPOSICAO DAS HABILIDADES NO TABULEIRO ---
    // Define os pontos de origem das habilidades (centro das matrizes)
    int origem_cone_l = 4, origem_cone_c = 4;   // Centro do cone
    int origem_cruz_l = 7, origem_cruz_c = 2;   // Centro da cruz
    int origem_octa_l = 7, origem_octa_c = 7;   // Centro do octaedro

    // Aplica as habilidades no tabuleiro
    aplica_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);
    aplica_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);
    aplica_habilidade(tabuleiro, octaedro, origem_octa_l, origem_octa_c);

    // --- EXIBE O TABULEIRO FINAL ---
    printf("Tabuleiro de Batalha Naval com Habilidades Especiais:\n\n");
    for (i = 0; i < TAM_TABULEIRO; i++) {
        for (j = 0; j < TAM_TABULEIRO; j++) {
            // Exibe simbolos diferentes para cada elemento
            if (tabuleiro[i][j] == 0)
                printf("~ "); // Agua
            else if (tabuleiro[i][j] == 3)
                printf("N "); // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* "); // Area de habilidade
            else
                printf("? "); // Caso inesperado
        }
        printf("\n");
    }

  getchar(); // Espera por uma entrada do usuario antes de fechar
printf("\nPressione Enter para sair...\n");
    return 0;
}
