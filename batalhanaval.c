#include <stdio.h>
#include <stdlib.h>

// Constantes para o tamanho do tabuleiro e habilidades
#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Constantes para representar os elementos no tabuleiro
#define AGUA 0
#define NAVIO 3
#define AREA_EFEITO 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para criar a matriz de habilidade em formato de Cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // O cone se expande à medida que desce na matriz
            // A linha superior tem apenas o ponto central
            // Cada linha abaixo tem mais pontos afetados
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // A cruz afeta a linha central e a coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // O octaedro forma um losango: a distância do centro determina se está afetado
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_origem, int coluna_origem) {
    
    // Calcula o deslocamento para centralizar a habilidade no ponto de origem
    int deslocamento = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula as coordenadas no tabuleiro
            int linha_tab = linha_origem - deslocamento + i;
            int coluna_tab = coluna_origem - deslocamento + j;
            
            // Verifica se as coordenadas estão dentro dos limites do tabuleiro
            if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO && 
                coluna_tab >= 0 && coluna_tab < TAM_TABULEIRO) {
                
                // Se a posição na matriz de habilidade está afetada, marca no tabuleiro
                if (habilidade[i][j] == 1) {
                    tabuleiro[linha_tab][coluna_tab] = AREA_EFEITO;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro com áreas de efeito:\n");
    printf("  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf(" ~ ");  // Água
                    break;
                case NAVIO:
                    printf(" █ ");  // Navio
                    break;
                case AREA_EFEITO:
                    printf(" * ");  // Área afetada pela habilidade
                    break;
                default:
                    printf(" ? ");  // Valor desconhecido
            }
        }
        printf("\n");
    }
}

// Função para exibir uma matriz de habilidade (para debug)
void exibirHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], const char* nome) {
    printf("\nMatriz de habilidade %s (%dx%d):\n", nome, TAM_HABILIDADE, TAM_HABILIDADE);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // Adiciona alguns navios para visualização
    tabuleiro[2][2] = NAVIO;
    tabuleiro[5][5] = NAVIO;
    tabuleiro[7][3] = NAVIO;
    tabuleiro[3][7] = NAVIO;
    tabuleiro[8][8] = NAVIO;
    
    // Cria as matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Exibe as matrizes de habilidade (opcional, para verificação)
    exibirHabilidade(cone, "Cone");
    exibirHabilidade(cruz, "Cruz");
    exibirHabilidade(octaedro, "Octaedro");
    
    // Define os pontos de origem para cada habilidade
    int cone_linha = 3, cone_coluna = 3;
    int cruz_linha = 6, cruz_coluna = 6;
    int octaedro_linha = 8, octaedro_coluna = 2;
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, cone_linha, cone_coluna);
    aplicarHabilidade(tabuleiro, cruz, cruz_linha, cruz_coluna);
    aplicarHabilidade(tabuleiro, octaedro, octaedro_linha, octaedro_coluna);
    
    // Exibe o tabuleiro final com as áreas de efeito
    exibirTabuleiro(tabuleiro);
    
    // Legenda
    printf("\nLegenda:\n");
    printf(" ~  - Água\n");
    printf(" █  - Navio\n");
    printf(" *  - Área afetada por habilidade\n");
    
    return 0;
}