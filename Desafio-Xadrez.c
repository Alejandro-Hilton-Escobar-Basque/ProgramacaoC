#include <stdio.h>

/*
    xadrez.c — Nível Mestre

    Peças:
    - Torre: recursivo (direita, 5 casas)
    - Bispo: recursivo (cima, direita, 5 casas) e também com loops aninhados (externo vertical, interno horizontal)
    - Rainha: recursivo (esquerda, 8 casas)
    - Cavalo: loops aninhados com múltiplas variáveis e condições (duas casas para cima e uma para a direita),
              utilizando continue e break para controle de fluxo.

    Observações:
    - Saída separada por linhas em branco entre peças.
    - Variáveis inteiras e strings, sem validação de entrada.
    - Recursão com casos base para evitar chamadas excessivas.
*/

/* -----------------------------------
   Funções recursivas para as peças
----------------------------------- */

// Torre recursiva: imprime "Direita" n vezes
void moverTorreDireitaRec(int casas) {
    if (casas <= 0) return;            // caso base: nada a mover
    printf("Direita\n");               // ação desta casa
    moverTorreDireitaRec(casas - 1);   // chamada recursiva para a próxima casa
}

// Bispo recursivo: imprime "Cima, Direita" n vezes
void moverBispoCimaDireitaRec(int casas) {
    if (casas <= 0) return;
    printf("Cima, Direita\n");
    moverBispoCimaDireitaRec(casas - 1);
}

// Rainha recursiva: imprime "Esquerda" n vezes
void moverRainhaEsquerdaRec(int casas) {
    if (casas <= 0) return;
    printf("Esquerda\n");
    moverRainhaEsquerdaRec(casas - 1);
}

/* -------------------------------------------------
   Bispo com loops aninhados (externo vertical,
   interno horizontal) — demonstração estruturada
------------------------------------------------- */
void moverBispoAninhado(int vertical, int horizontal) {
    // Loop externo controla passos no eixo vertical (Cima)
    for (int v = 0; v < vertical; v++) {
        // Loop interno controla passos no eixo horizontal (Direita)
        for (int h = 0; h < horizontal; h++) {
            // Cada iteração representa avançar uma casa na diagonal combinando vertical e horizontal
            printf("Cima, Direita\n");
        }
    }
}

/* -----------------------------------
   Cavalo com loops aninhados complexos
   Movimento: 2 para cima, 1 para direita
----------------------------------- */
void moverCavaloCimaDireitaComplexo(void) {
    int passosCimaAlvo = 2;
    int passosDireitaAlvo = 1;

    int passosCima = 0;
    int passosDireita = 0;

    // Loop externo controla progresso total; usa múltiplas condições
    for (int iter = 0; iter < 10; iter++) { // limite seguro para evitar loops infinitos
        // Se já concluímos os 3 passos do "L", interrompe
        if (passosCima == passosCimaAlvo && passosDireita == passosDireitaAlvo) {
            break;
        }

        // Loop interno tenta executar um passo por ciclo
        // Alterna prioridade: primeiro completar "Cima", depois "Direita"
        for (int fase = 0; fase < 2; fase++) {
            // Se já concluímos tudo, saia do loop interno
            if (passosCima == passosCimaAlvo && passosDireita == passosDireitaAlvo) {
                break;
            }

            // Fase 0: mover Cima (até 2); Fase 1: mover Direita (até 1)
            if (fase == 0) {
                // Se já atingiu o alvo de "Cima", pula para próximo
                if (passosCima >= passosCimaAlvo) {
                    continue;
                }
                printf("Cima\n");
                passosCima++;
                // Pequena regra de fluxo: se por algum motivo exceder (defesa), interrompe
                if (passosCima > passosCimaAlvo) {
                    break;
                }
            } else {
                if (passosDireita >= passosDireitaAlvo) {
                    continue;
                }
                printf("Direita\n");
                passosDireita++;
                if (passosDireita > passosDireitaAlvo) {
                    break;
                }
            }
        }
    }
}

int main() {
    // ==============================
    // Torre (recursivo) — 5 casas
    // ==============================
    printf("Movimento da Torre (recursivo):\n");
    moverTorreDireitaRec(5);

    // Linha em branco para separar saídas
    printf("\n");

    // ==============================
    // Bispo (recursivo) — 5 casas
    // ==============================
    printf("Movimento do Bispo (recursivo):\n");
    moverBispoCimaDireitaRec(5);

    // ==============================
    // Bispo (loops aninhados)
    // externo: vertical / interno: horizontal
    // Demonstra 5 passos combinados como 5x1
    // ==============================
    printf("\nMovimento do Bispo (loops aninhados):\n");
    moverBispoAninhado(5, 1);

    // Linha em branco para separar saídas
    printf("\n");

    // ==============================
    // Rainha (recursivo) — 8 casas
    // ==============================
    printf("Movimento da Rainha (recursivo):\n");
    moverRainhaEsquerdaRec(8);

    // Linha em branco para separar saídas
    printf("\n");

    // ==============================
    // Cavalo (loops aninhados complexos)
    // Movimento: 2 para Cima, 1 para Direita
    // ==============================
    printf("Movimento do Cavalo (loops complexos):\n");
    moverCavaloCimaDireitaComplexo();

    return 0;
}
