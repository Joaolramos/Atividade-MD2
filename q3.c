#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

/**
 * @brief Calcula a potência inteira (base^exp).
 * Mais seguro que pow() de math.h para aritmética inteira,
 * pois evita erros de precisão de ponto flutuante.
 */
ll int_pow(int base, int exp) {
    ll resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }
    return resultado;
}

/**
 * @brief Função principal que fatora N e calcula tau, sigma e a razão.
 * @param N O número de entrada original.
 */
void calcularRazaodeEficiencia(int N) {
    printf("--- Iniciando Fatoracao de N = %d (Metodo: Trial Division) ---\n", N);
    
    int n_temp = N; // Cópia de N que será modificada durante a fatoração
    ll tau_N = 1;     // Acumulador para tau(N)
    ll sigma_N = 1;   // Acumulador para sigma(N)

    // --- Etapa 1: Tratar Fator 2 (números pares) ---
    // Tratamos o 2 separadamente para podermos pular de 2 em 2 depois.
    if (n_temp % 2 == 0) {
        int expoente = 0; // Este é o 'a'
        while (n_temp % 2 == 0) {
            n_temp /= 2;
            expoente++;
        }
        
        printf("  Fator encontrado: 2^%d\n", expoente);
        int p = 2; // O fator primo 'p'

        // 1. Cálculo de tau(N) = (a1 + 1) * ...
        ll tau_antigo = tau_N;
        tau_N *= (expoente + 1);
        printf("    -> tau(N) = %lld * (%d + 1) = %lld\n", tau_antigo, expoente, tau_N);

        // 2. Cálculo de sigma(N) = [(p1^(a1+1) - 1) / (p1 - 1)] * ...
        ll sigma_antigo = sigma_N;
        ll p_a_mais_1 = int_pow(p, expoente + 1); // p^(a+1)
        ll soma_divisor = (p_a_mais_1 - 1) / (p - 1); // (p^(a+1) - 1) / (p-1)
        sigma_N *= soma_divisor;
        printf("    -> sigma(N) = %lld * ((%d^%d - 1) / (%d - 1)) = %lld * %lld = %lld\n",
               sigma_antigo, p, expoente + 1, p, sigma_antigo, soma_divisor, sigma_N);
    }

    // --- Etapa 2: Tratar Fatores Ímpares (a partir de 3) ---
    // Começa em 3 e testa apenas ímpares (divisor += 2)
    // O loop vai até divisor <= sqrt(n_temp)
    for (int divisor = 3; divisor * divisor <= n_temp; divisor += 2) {
        if (n_temp % divisor == 0) {
            int expoente = 0;
            while (n_temp % divisor == 0) {
                n_temp /= divisor;
                expoente++;
            }
            
            printf("  Fator encontrado: %d^%d\n", divisor, expoente);
            int p = divisor;

            // 1. Cálculo de tau(N)
            ll tau_antigo = tau_N;
            tau_N *= (expoente + 1);
            printf("    -> tau(N) = %lld * (%d + 1) = %lld\n", tau_antigo, expoente, tau_N);

            // 2. Cálculo de sigma(N)
            ll sigma_antigo = sigma_N;
            ll p_a_mais_1 = int_pow(p, expoente + 1);
            ll soma_divisor = (p_a_mais_1 - 1) / (p - 1);
            sigma_N *= soma_divisor;
            printf("    -> sigma(N) = %lld * ((%d^%d - 1) / (%d - 1)) = %lld * %lld = %lld\n",
                   sigma_antigo, p, expoente + 1, p, sigma_antigo, soma_divisor, sigma_N);
        }
    }

    // --- Etapa 3: Tratar Fator Restante ---
    // Se n_temp > 1, significa que o que sobrou é um fator primo
    // (Ex: N=14. Fator 2^1 -> n_temp=7. Loop 'for' não roda. n_temp=7 > 1)
    if (n_temp > 1) {
        int p_restante = n_temp;
        int expoente = 1; // O expoente será sempre 1
        
        printf("  Fator restante: %d^%d\n", p_restante, expoente);

        // 1. Cálculo de tau(N)
        ll tau_antigo = tau_N;
        tau_N *= (expoente + 1);
        printf("    -> tau(N) = %lld * (%d + 1) = %lld\n", tau_antigo, expoente, tau_N);

        // 2. Cálculo de sigma(N)
        // Otimização: (p^(1+1) - 1) / (p - 1) = (p^2 - 1) / (p - 1) = (p+1)
        ll sigma_antigo = sigma_N;
        ll soma_divisor = p_restante + 1;
        sigma_N *= soma_divisor;
        printf("    -> sigma(N) = %lld * (%d + 1) = %lld * %lld = %lld\n",
               sigma_antigo, p_restante, sigma_antigo, soma_divisor, sigma_N);
    }
    
    printf("--- Fatoracao Concluida ---\n");

    // --- Etapa 4: Calcular a Razão de Eficiência ---
    printf("\nCalculos Finais:\n");
    printf("  tau(N)   = %lld\n", tau_N);   // Número total de divisores
    printf("  sigma(N) = %lld\n", sigma_N); // Soma total de divisores
    
    // Convertemos para 'double' para a divisão real
    double numerador = (double)(sigma_N - 1);
    double denominador = (double)N * (double)tau_N; // Usa o N *original*
    double razao = 0.0;
    
    if (denominador != 0) {
        razao = numerador / denominador;
    }

    printf("\n--- Razao de Eficiencia de %d ---\n", N);
    // Imprime a fórmula
    printf("(sigma(N) - 1) / (N * tau(N)) = (%lld - 1) / (%d * %lld)\n", sigma_N, N, tau_N);
    // Imprime os valores calculados
    printf("= %.0f / %.0f\n", numerador, denominador);
    // Imprime o resultado final formatado
    printf("Razao = %.2f\n", razao);
}

int main() {
    printf("==================================================\n");
    printf("  CALCULO DA RAZAO DE EFICIENCIA DE UM NUMERO\n");
    printf("==================================================\n");
    
    int N;
    printf("Digite um inteiro N (1 <= N <= 100000): ");
    scanf("%d", &N);

    // Validação da entrada
    if (N < 1 || N > 100000) {
        printf("Entrada invalida. O numero deve estar entre 1 e 100000.\n");
        return 1; // Encerra com erro
    }

    // --- Tratar caso especial N=1 ---
    // N=1 não tem fatores primos.
    // tau(1) = 1 (divisor é 1)
    // sigma(1) = 1 (soma do divisor 1)
    if (N == 1) {
        printf("--- Fatoracao de N = 1 ---\n");
        printf("  Nao ha fatores primos.\n");
        printf("Calculos Finais:\n");
        printf("  tau(1) = 1\n");
        printf("  sigma(1) = 1\n");
        printf("\n--- Razao de Eficiencia de 1 ---\n");
        printf("(sigma(1) - 1) / (1 * tau(1)) = (1 - 1) / (1 * 1)\n");
        printf("= 0.0 / 1.0\n");
        printf("Razao = 0.00\n");
    } else {
        // Chama a função principal para N > 1
        calcularRazaodeEficiencia(N);
    }

    return 0;
}