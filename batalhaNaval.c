#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define TAMANHO_NAVIO 3


void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}


bool posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO && 
           coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}


bool podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    return posicaoValida(linha, coluna) && tabuleiro[linha][coluna] == AGUA;
}


bool posicionarNavioReto(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int linha, int coluna, bool horizontal) {
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = horizontal ? linha : linha + i;
        int novaColuna = horizontal ? coluna + i : coluna;
        
        if (!podePosicionar(tabuleiro, novaLinha, novaColuna)) {
            return false;
        }
    }
    
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = horizontal ? linha : linha + i;
        int novaColuna = horizontal ? coluna + i : coluna;
        
        tabuleiro[novaLinha][novaColuna] = NAVIO;
    }
    
    return true;
}


bool posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                            int linha, int coluna, bool diagonalPrincipal) {
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha + i;
        int novaColuna = diagonalPrincipal ? coluna + i : coluna - i;
        
        if (!podePosicionar(tabuleiro, novaLinha, novaColuna)) {
            return false;
        }
    }
    
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha + i;
        int novaColuna = diagonalPrincipal ? coluna + i : coluna - i;
        
        tabuleiro[novaLinha][novaColuna] = NAVIO;
    }
    
    return true;
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n\n");
    

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
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    
    inicializarTabuleiro(tabuleiro);
    
    printf("Posicionando navios...\n");
    

    if (!posicionarNavioReto(tabuleiro, 2, 3, true)) {
        printf("Erro ao posicionar navio horizontal 1!\n");
        return 1;
    }
    
    
    if (!posicionarNavioReto(tabuleiro, 5, 7, false)) {
        printf("Erro ao posicionar navio vertical 2!\n");
        return 1;
    }
    

    if (!posicionarNavioDiagonal(tabuleiro, 1, 1, true)) {
        printf("Erro ao posicionar navio diagonal principal 3!\n");
        return 1;
    }
    
    
    if (!posicionarNavioDiagonal(tabuleiro, 6, 8, false)) {
        printf("Erro ao posicionar navio diagonal secundária 4!\n");
        return 1;
    }
    
    
    exibirTabuleiro(tabuleiro);
    
    return 0;
}