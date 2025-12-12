#include <stdio.h>
#include <stdlib.h> // Para a função abs()

// --- Constantes e Tipos ---

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 7 // Tamanho fixo 7x7 para as matrizes de habilidade (ímpar para centro)

#define AGUA 0
#define MARCA_NAVIO 3
#define MARCA_HABILIDADE 5 // Novo valor para representar a área de efeito

// Enumeração para o tipo de habilidade
typedef enum {
    HAB_CONE,
    HAB_CRUZ,
    HAB_OCTAEDRO
} TipoHabilidade;

// --- Funções do Nível Aventureiro (Simplificadas para Foco) ---

void inicializar_tabuleiro(int t[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            t[i][j] = AGUA;
        }
    }
}

// Funções de posicionamento e validação de navios (omitidas para foco, mas necessárias)
// Apenas posicionamos os navios diretamente para simplificação:
void posicionar_navios_iniciais(int t[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio Horizontal (Linha 1, Coluna 1)
    for (int j = 0; j < TAMANHO_NAVIO; j++) t[1][1 + j] = MARCA_NAVIO;
    // Navio Vertical (Linha 4, Coluna 8)
    for (int i = 0; i < TAMANHO_NAVIO; i++) t[4 + i][8] = MARCA_NAVIO;
    // Navio Diagonal Baixo-Direita (Linha 7, Coluna 0)
    for (int k = 0; k < TAMANHO_NAVIO; k++) t[7 + k][0 + k] = MARCA_NAVIO;
}

// --- Funções do Nível Mestre: Criação e Aplicação de Habilidades ---

/**
 * @brief Cria a matriz de área de efeito para a Habilidade do TIPO CONE.
 * O cone aponta para baixo (se expande em linhas crescentes).
 * @param habilidade A matriz 7x7 que será preenchida (0 ou 1).
 */
void criar_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // Centro = 3 para 7x7

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) { // Linha (altura do cone)
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) { // Coluna (largura do cone)
            
            // Condicional: A largura do cone (j) na linha 'i' deve ser:
            // Centro - i <= j <= Centro + i
            // Isso cria a forma triangular/cônica.
            if (j >= centro - i && j <= centro + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de área de efeito para a Habilidade do TIPO CRUZ.
 * @param habilidade A matriz 7x7 que será preenchida (0 ou 1).
 */
void criar_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Condicional: A posição é marcada se estiver na Linha Central OU Coluna Central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria a matriz de área de efeito para a Habilidade do TIPO OCTAEDRO (Losango).
 * Utiliza a distância de Manhattan (abs(di) + abs(dj)).
 * @param habilidade A matriz 7x7 que será preenchida (0 ou 1).
 */
void criar_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    int raio = centro; // Raio máximo (3)

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Distância relativa ao centro (dr = delta row, dc = delta col)
            int dr = abs(i - centro);
            int dc = abs(j - centro);
            
            // Condicional: A soma das distâncias absolutas (Manhattan) deve ser menor ou igual ao raio
            // Isso gera o formato de losango (Octaedro)
            if (dr + dc <= raio) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Sobrepõe uma matriz de habilidade ao tabuleiro principal, centrada no ponto (origem_r, origem_c).
 * @param tabuleiro O tabuleiro 10x10 onde a habilidade será aplicada.
 * @param habilidade A matriz de habilidade 7x7 (com 0s e 1s).
 * @param origem_r Linha central onde a habilidade será aplicada.
 * @param origem_c Coluna central onde a habilidade será aplicada.
 */
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                        int origem_r, int origem_c) {
    
    int raio = TAMANHO_HABILIDADE / 2; // Raio (3)

    // Loops aninhados percorrem a matriz da HABILIDADE (i_hab, j_hab)
    for (int i_hab = 0; i_hab < TAMANHO_HABILIDADE; i_hab++) {
        for (int j_hab = 0; j_hab < TAMANHO_HABILIDADE; j_hab++) {
            
            // 1. Calcula a posição correspondente no TABULEIRO
            // Posição no Tabuleiro = Ponto de Origem + Deslocamento da Habilidade - Raio
            int i_tab = origem_r + (i_hab - raio);
            int j_tab = origem_c + (j_hab - raio);

            // 2. Condicional para a Sobreposição e Limites
            // Verifica se a posição no tabuleiro está dentro dos limites 0..9
            if (i_tab >= 0 && i_tab < TAMANHO_TABULEIRO &&
                j_tab >= 0 && j_tab < TAMANHO_TABULEIRO) {
                
                // Verifica se a célula da HABILIDADE está marcada (valor 1)
                if (habilidade[i_hab][j_hab] == 1) {
                    
                    // Condicional para marcar: Só marca se não for um navio (evita sobrescrever o 3)
                    // Se for água (0), aplica a marca da habilidade (5)
                    if (tabuleiro[i_tab][j_tab] == AGUA) {
                        tabuleiro[i_tab][j_tab] = MARCA_HABILIDADE;
                    }
                    // Se a posição já for um navio (3), não faz nada (mantém o 3).
                }
            }
        }
    }
}


/**
 * @brief Exibe o tabuleiro no console, usando caracteres visuais para diferenciação.
 * @param tabuleiro A matriz do tabuleiro a ser exibida.
 */
void exibir_tabuleiro_visual(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n======================================================\n");
    printf("🎯 Tabuleiro Final (Navios e Areas de Efeito) 🎯\n");
    printf("   (0 = AGUA, 3 = NAVIO, 5 = EFEITO)\n");
    printf("   "); 

    // Imprime cabeçalho das colunas (0 a 9)
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    // Imprime o conteúdo do tabuleiro com caracteres
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo;
            if (tabuleiro[i][j] == AGUA) {
                simbolo = '~'; // Água
            } else if (tabuleiro[i][j] == MARCA_NAVIO) {
                simbolo = 'N'; // Navio
            } else if (tabuleiro[i][j] == MARCA_HABILIDADE) {
                simbolo = 'X'; // Área de Efeito
            } else {
                simbolo = '?'; // Fallback
            }
            printf(" %c", simbolo); 
        }
        printf(" |\n");
    }
    printf("======================================================\n");
}

// --- Função Principal ---

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Matrizes fixas para as habilidades (7x7)
    int hab_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int hab_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int hab_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // --- 1. Inicializa o Tabuleiro e Posiciona Navios ---
    inicializar_tabuleiro(tabuleiro);
    posicionar_navios_iniciais(tabuleiro);
    
    printf("Navios iniciais posicionados no tabuleiro.\n");
    
    // --- 2. Cria as Matrizes de Habilidade (Usando Condicionais) ---
    criar_cone(hab_cone);
    criar_cruz(hab_cruz);
    criar_octaedro(hab_octaedro);
    
    printf("Matrizes de Habilidade (Cone, Cruz, Octaedro) geradas com sucesso.\n");
    
    // --- 3. Aplica as Habilidades no Tabuleiro (Definindo Pontos de Origem) ---

    // Habilidade 1: Cone (Centrado em [5, 5])
    int origem_cone_r = 5;
    int origem_cone_c = 5;
    aplicar_habilidade(tabuleiro, hab_cone, origem_cone_r, origem_cone_c);
    printf("Habilidade Cone aplicada (Origem: %d, %d).\n", origem_cone_r, origem_cone_c);

    // Habilidade 2: Cruz (Centrado em [2, 8]) - Sobrepõe a área de um navio (vertical)
    int origem_cruz_r = 2;
    int origem_cruz_c = 8;
    aplicar_habilidade(tabuleiro, hab_cruz, origem_cruz_r, origem_cruz_c);
    printf("Habilidade Cruz aplicada (Origem: %d, %d).\n", origem_cruz_r, origem_cruz_c);

    // Habilidade 3: Octaedro (Losango) (Centrado em [8, 3]) - Toca os limites
    int origem_octaedro_r = 8;
    int origem_octaedro_c = 3;
    aplicar_habilidade(tabuleiro, hab_octaedro, hab_octaedro, origem_octaedro_r, origem_octaedro_c);
    printf("Habilidade Octaedro aplicada (Origem: %d, %d).\n", origem_octaedro_r, origem_octaedro_c);

    // --- 4. Exibe o Tabuleiro Final ---
    exibir_tabuleiro_visual(tabuleiro);
    
    // 

    return 0;
}
