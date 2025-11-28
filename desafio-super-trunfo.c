#include <stdio.h>

int main() {
    // Dados da Carta 1
    char nome1[] = "Sao Paulo";
    int populacao1 = 12325000;
    float area1 = 1521.11;
    float pib1 = 699.28; // bilhões
    int pontos1 = 50;
    float densidade1 = populacao1 / area1;
    float pibPerCapita1 = (pib1 * 1000000000) / populacao1;

    // Dados da Carta 2
    char nome2[] = "Rio de Janeiro";
    int populacao2 = 6748000;
    float area2 = 1200.25;
    float pib2 = 300.50; // bilhões
    int pontos2 = 30;
    float densidade2 = populacao2 / area2;
    float pibPerCapita2 = (pib2 * 1000000000) / populacao2;

    // Variáveis para comparação
    int attr1, attr2;
    float v1_attr1, v2_attr1, v1_attr2, v2_attr2;
    float soma1, soma2;

    // Menu para escolher atributos
    printf("Escolha o PRIMEIRO atributo:\n");
    printf("1 - Populacao\n");
    printf("2 - Area (km²)\n");
    printf("3 - PIB (bilhoes de reais)\n");
    printf("4 - Densidade demografica (MENOR vence)\n");
    printf("5 - PIB per capita (reais)\n");
    printf("6 - Pontos turisticos\n");
    scanf("%d", &attr1);

    printf("\nEscolha o SEGUNDO atributo (diferente do primeiro):\n");
    scanf("%d", &attr2);

    // Atribui valores do primeiro atributo
    switch (attr1) {
        case 1: v1_attr1 = populacao1; v2_attr1 = populacao2; break;
        case 2: v1_attr1 = area1; v2_attr1 = area2; break;
        case 3: v1_attr1 = pib1; v2_attr1 = pib2; break;
        case 4: v1_attr1 = densidade1; v2_attr1 = densidade2; break;
        case 5: v1_attr1 = pibPerCapita1; v2_attr1 = pibPerCapita2; break;
        case 6: v1_attr1 = pontos1; v2_attr1 = pontos2; break;
        default: printf("Atributo invalido!\n"); return 0;
    }

    // Atribui valores do segundo atributo
    switch (attr2) {
        case 1: v1_attr2 = populacao1; v2_attr2 = populacao2; break;
        case 2: v1_attr2 = area1; v2_attr2 = area2; break;
        case 3: v1_attr2 = pib1; v2_attr2 = pib2; break;
        case 4: v1_attr2 = densidade1; v2_attr2 = densidade2; break;
        case 5: v1_attr2 = pibPerCapita1; v2_attr2 = pibPerCapita2; break;
        case 6: v1_attr2 = pontos1; v2_attr2 = pontos2; break;
        default: printf("Atributo invalido!\n"); return 0;
    }

    // Soma dos atributos
    soma1 = v1_attr1 + v1_attr2;
    soma2 = v2_attr1 + v2_attr2;

    // Exibe resultados
    printf("\nComparacao entre %s e %s:\n", nome1, nome2);
    printf("Atributo 1: %.2f vs %.2f\n", v1_attr1, v2_attr1);
    printf("Atributo 2: %.2f vs %.2f\n", v1_attr2, v2_attr2);
    printf("Soma dos atributos: %.2f vs %.2f\n", soma1, soma2);

    // Decide vencedor (densidade é exceção: menor vence)
    if (attr1 == 4) {
        if (v1_attr1 < v2_attr1) printf("%s venceu no atributo 1!\n", nome1);
        else if (v2_attr1 < v1_attr1) printf("%s venceu no atributo 1!\n", nome2);
        else printf("Empate no atributo 1!\n");
    } else
