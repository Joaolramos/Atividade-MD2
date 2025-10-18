#include <stdio.h>
#include <stdbool.h>

int main() {
    int N; // Número de chaves
    int ciclos[10]; // Array para guardar os N ciclos (max N=10)
    int i, ano;

    // --- 1. Entrada de Dados ---
    
    // Lê a primeira linha (N)
    scanf("%d", &N);

    // Lê a segunda linha (os N ciclos)
    for (i = 0; i < N; i++) {
        scanf("%d", &ciclos[i]);
    }

    // --- 2. Processamento (Simulação) ---

    int anoSincronizado = -1; // -1 significa "não encontrado"

    // Itera por cada ano, do ano 1 até o limite 50
    for (ano = 1; ano <= 50; ano++) {
        
        bool anoValido = true; // Assume que o ano 'ano' é válido

        // Verifica o 'ano' contra CADA ciclo
        for (i = 0; i < N; i++) {
            
            // Se o ano NÃO for múltiplo de ALGUM dos ciclos...
            // (O resto da divisão % é diferente de 0)
            if (ano % ciclos[i] != 0) {
                anoValido = false; // ...o ano é inválido.
                break; // Para de verificar este ano e vai para o próximo.
            }
        }

        // Se, após verificar todos os ciclos, o ano continuou válido...
        if (anoValido) {
            anoSincronizado = ano; // ...encontramos o primeiro!
            break; // Para o loop principal, pois queremos apenas o PRIMEIRO.
        }
    }

    // --- 3. Saída ---

    // Se encontramos um ano (o valor mudou de -1)
    if (anoSincronizado != -1) {
        printf("%d\n", anoSincronizado);
    } 
    // Se o loop terminou e 'anoSincronizado' ainda é -1
    else {
        printf("Nao ha ano sincronizado dentro do limite de 50 anos.\n");
    }

    return 0;
}