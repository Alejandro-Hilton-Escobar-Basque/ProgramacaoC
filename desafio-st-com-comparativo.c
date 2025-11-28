#include <stdio.h>

// Função auxiliar para limpar o buffer da entrada
void limparEntrada() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

// Retorna a descrição do atributo
const char* nomeAtributo(int id) {
    switch (id) {
        case 1: return "Populacao";
        case 2: return "Area (km²)";
        case 3: return "PIB (bilhoes de reais)";
        case 4: return "Pontos turisticos";
        case 5: return "Densidade demografica (hab/km²) [MENOR vence]";
        case 6: return "PIB per capita (reais)";
        default: return "Atributo invalido";
    }
}

// Retorna o valor numérico do atributo para a Carta 1
float valorAtributoCarta1(int id,
                          int populacao, float area, float pibBilhoes, int pontos,
                          float densidade, float pibPerCapita) {
    switch (id) {
        case 1: return (float)populacao;
        case 2: return area;
        case 3: return pibBilhoes;
        case 4: return (float)pontos;
        case 5: return densidade;
        case 6: return pibPerCapita;
        default: return 0.0f;
    }
}

// Retorna o valor numérico do atributo para a Carta 2
float valorAtributoCarta2(int id,
                          int populacao, float area, float pibBilhoes, int pontos,
                          float densidade, float pibPerCapita) {
    switch (id) {
        case 1: return (float)populacao;
        case 2: return area;
        case 3: return pibBilhoes;
        case 4: return (float)pontos;
        case 5: return densidade;
        case 6: return pibPerCapita;
        default: return 0.0f;
    }
}

// Compara um atributo entre as duas cartas
int compararAtributo(float v1, float v2, int atributoId) {
    int densidadeMenorVence = (atributoId == 5);
    if (densidadeMenorVence) {
        if (v1 < v2) return 1;
        else if (v2 < v1) return 2;
        else return 0;
    } else {
        if (v1 > v2) return 1;
        else if (v2 > v1) return 2;
        else return 0;
    }
}

int main() {
    // Cadastro das cartas (nível básico)
    char nome1[] = "Sao Paulo";
    int populacao1 = 12325000;
    float area1 = 1521.11f;
    float pib1 = 699.28f; // bilhões
    int pontos1 = 50;

    char nome2[] = "Rio de Janeiro";
    int populacao2 = 6748000;
    float area2 = 1200.25f;
    float pib2 = 300.50f; // bilhões
    int pontos2 = 30;

    // Cálculos adicionais (nível aventureiro)
    float densidade1 = populacao1 / area1;
    float densidade2 = populacao2 / area2;
    float pibPerCapita1 = (pib1 * 1000000000.0f) / populacao1;
    float pibPerCapita2 = (pib2 * 1000000000.0f) / populacao2;

    // Exibição das cartas
    printf("\n--- Carta 1 ---\n");
    printf("Nome da Cidade: %s\n", nome1);
    printf("Populacao: %d\n", populacao1);
    printf("Area: %.2f km²\n", area1);
    printf("PIB: %.2f bilhoes de reais\n", pib1);
    printf("Pontos Turisticos: %d\n", pontos1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita1);

    printf("\n--- Carta 2 ---\n");
    printf("Nome da Cidade: %s\n", nome2);
    printf("Populacao: %d\n", populacao2);
    printf("Area: %.2f km²\n", area2);
    printf("PIB: %.2f bilhoes de reais\n", pib2);
    printf("Pontos Turisticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita2);

    // Interatividade (nível mestre)
    int attr1 = -1, attr2 = -1;

    // Primeiro atributo
    while (1) {
        int ok = 1;
        printf("\nEscolha o PRIMEIRO atributo:\n");
        for (int i = 1; i <= 6; i++) {
            printf("%d - %s\n", i, nomeAtributo(i));
        }
        printf("Opcao: ");
        if (scanf("%d", &attr1) != 1) { ok = 0; }
        limparEntrada();
        if (ok && attr1 >= 1 && attr1 <= 6) break;
        printf("Opcao invalida. Tente novamente.\n");
    }

    // Segundo atributo (não pode repetir)
    while (1) {
        int ok = 1;
        printf("\nEscolha o SEGUNDO atributo (diferente do primeiro):\n");
        for (int i = 1; i <= 6; i++) {
            if (i == attr1) continue;
            printf("%d - %s\n", i, nomeAtributo(i));
        }
        printf("Opcao: ");
        if (scanf("%d", &attr2) != 1) { ok = 0; }
        limparEntrada();
        if (ok && attr2 >= 1 && attr2 <= 6 && attr2 != attr1) break;
        printf("Opcao invalida ou repetida. Tente novamente.\n");
    }

    // Valores dos atributos
    float v1_attr1 = valorAtributoCarta1(attr1, populacao1, area1, pib1, pontos1, densidade1, pibPerCapita1);
    float v2_attr1 = valorAtributoCarta2(attr1, populacao2, area2, pib2, pontos2, densidade2, pibPerCapita2);

    float v1_attr2 = valorAtributoCarta1(attr2, populacao1, area1, pib1, pontos1, densidade1, pibPerCapita1);
    float v2_attr2 = valorAtributoCarta2(attr2, populacao2, area2, pib2, pontos2, densidade2, pibPerCapita2);

    // Comparações
    int vencedor1 = compararAtributo(v1_attr1, v2_attr1, attr1);
    int vencedor2 = compararAtributo(v1_attr2, v2_attr2, attr2);

    // Soma dos atributos
    float soma1 = v1_attr1 + v1_attr2;
    float soma2 = v2_attr1 + v2_attr2;

    // Resultado final com operador ternário
    int vencedorFinal = (soma1 > soma2) ? 1 : (soma2 > soma1) ? 2 : 0;

    // Exibição dos resultados
    printf("\n================ Resultado da Comparacao ================\n");
    printf("Cartas: %s vs %s\n", nome1, nome2);

    printf("\nAtributo 1: %s\n", nomeAtributo(attr1));
    printf(" - %s: %.2f\n", nome1, v1_attr1);
    printf(" - %s: %.2f\n", nome2, v2_attr1);
    printf("Vencedor no atributo 1: %s\n",
           vencedor1 == 1 ? nome1 : vencedor1 == 2 ? nome2 : "Empate");

    printf("\nAtributo 2: %s\n", nomeAtributo(attr2));
    printf(" - %s: %.2f\n", nome1, v1_attr2);
    printf(" - %s: %.2f\n", nome2, v2_attr2);
    printf("Vencedor no atributo 2: %s\n",
           vencedor2 == 1 ? nome1 : vencedor2 == 2 ? nome2 : "Empate");

    printf("\nSoma dos atributos:\n");
    printf(" - %s: %.2f\n", nome1, soma1);
    printf(" - %s: %.2f\n", nome2, soma2);

    if (vencedorFinal == 1) {
        printf("\nResultado final: %s VENCEU a rodada!\n", nome1);
