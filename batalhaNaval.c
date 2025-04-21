#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5


void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}


void posicionarNavios(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    
    tabuleiro[2][3] = 3;
    tabuleiro[5][7] = 3;
    tabuleiro[8][1] = 3;
    tabuleiro[3][8] = 3;
    tabuleiro[7][4] = 3;
    tabuleiro[1][1] = 3;
    tabuleiro[9][9] = 3;
    tabuleiro[4][5] = 3;
}


void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (i == TAM_HABILIDADE/2 || j == TAM_HABILIDADE/2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE/2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}


void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_centro, int coluna_centro) {
    
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            int tab_linha = linha_centro - offset + i;
            int tab_coluna = coluna_centro - offset + j;
            
            
            if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO && 
                tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                
                if (habilidade[i][j] == 1) {
                    // Não sobrescreve navios (valor 3)
                    if (tabuleiro[tab_linha][tab_coluna] != 3) {
                        tabuleiro[tab_linha][tab_coluna] = 5;
                    }
                }
            }
        }
    }
}


void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            switch(tabuleiro[i][j]) {
                case 0: printf(" ~ "); break;  
                case 3: printf(" \u25A0 "); break; 
                case 5: printf(" * "); break; 
                default: printf(" ? "); break;
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    
    
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    
    aplicarHabilidade(tabuleiro, cone, 3, 3);      
    aplicarHabilidade(tabuleiro, cruz, 7, 2);      
    aplicarHabilidade(tabuleiro, octaedro, 5, 7);  
    
    exibirTabuleiro(tabuleiro);
    
    return 0;
}