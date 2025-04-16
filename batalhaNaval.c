#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3


void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}


bool posicaoValida(int linha, int coluna, int tamanho, bool vertical) {
    if (vertical) {
        return (linha >= 0) && (linha + tamanho - 1 < TAMANHO_TABULEIRO) && 
               (coluna >= 0) && (coluna < TAMANHO_TABULEIRO);
    } else {
        return (linha >= 0) && (linha < TAMANHO_TABULEIRO) && 
               (coluna >= 0) && (coluna + tamanho - 1 < TAMANHO_TABULEIRO);
    }
}


bool semSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical) {
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] == NAVIO) {
                return false;
            }
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] == NAVIO) {
                return false;
            }
        }
    }
    return true;
}


bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical) {
    // Verifica se a posição é válida
    if (!posicaoValida(linha, coluna, tamanho, vertical)) {
        printf("Posição inválida para o navio!\n");
        return false;
    }
    
    
    if (!semSobreposicao(tabuleiro, linha, coluna, tamanho, vertical)) {
        printf("Navio sobreposto a outro navio!\n");
        return false;
    }
    
    
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    }
    
    return true;
}


void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); 
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    
    inicializarTabuleiro(tabuleiro);
    
    
    bool navioHorizontalPosicionado = posicionarNavio(tabuleiro, 2, 3, TAMANHO_NAVIO, false);
    
    
    bool navioVerticalPosicionado = posicionarNavio(tabuleiro, 5, 7, TAMANHO_NAVIO, true);
    
    
    if (!navioHorizontalPosicionado || !navioVerticalPosicionado) {
        printf("Erro ao posicionar os navios. Verifique as coordenadas.\n");
        return 1;
    }
    
    
    imprimirTabuleiro(tabuleiro);
    
    return 0;
}